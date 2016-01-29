import glob
import random
import numpy as np
import cv2 #TODO remove it from here, in order to load openCV only when needed
import time
from simpleDrawing import loadBar

if int(cv2.__version__.split('.')[0]) != 3:
	print("Error, OpenCV 3 needed")
	raise Exception("OpenCV 3 needed")

class KeyPoint:
	"""
		My own keypoint class, to avoid the openCV dependancy here
	"""
	#TODO
	def __init__(self):
		pass

def select_image(roomlist, directory, nb_image=-1):
	"""
		Return a list of nb_image images (default 10) 
		randomly choosen in the given directory
		imageName is the type of name to select
	"""
	print("Directory ="+directory)
	l = []
	for r in roomlist: #read all image in the given rooms
		for x in glob.glob(directory+r+'[A-Z]-*.JPG'):
			l.append(x)
	imageList = []
	if nb_image == -1:
		return l
	if len(l) > 0:
		while len(imageList) < nb_image: #select only nb_image images
			imageList.append(random.choice(l))
	else:
		return []
	return imageList

def extractFeatures(imName, extractor):
	im = cv2.imread(imName)
	return extractor.detectAndCompute(im, None)
	
class Library:
	def __init__(self, descType="ORB"):
		self.nbImage = 0
		self.descType=descType
		if(descType=='BRISK'):
			import cv2
			self.extractor = cv2.BRISK_create()
		elif(descType=='AKAZE'):
			import cv2
			self.extractor = cv2.AKAZE_create()
		elif(descType=="SIFT"):
			import cv2
			self.extractor=cv2.xfeatures2d.SIFT_create()
		else:
			print("Descriptor not found - ORB selectionned")
			import cv2
			self.extractor = cv2.ORB_create()
		
		
	def addDirectory(directory, nbimage=-1):
		self.imlist = select_image([str(x) for x in range(1, 45)], directory, nbimage)
		self.nbImage = len(self.imlist)
		c = time.clock()
		self.images = [(imname,extractFeatures(imname, extractor)) for imname in imlist]
		elapsed = time.clock() - c
		print("Time to extract all features : ", elapsed)
		print("Time for each image :", elapsed/len(images))
		
		
	def save(self, filename):
		print("Save image list")
		with open(filename,'w') as f:
			t = time.clock()
			f.write(str(self.nbImage))
			f.write('\n')
			for j,(name, (klist, dlist)) in enumerate(self.images):
				f.write(name+'\n'+str(len(klist)) + '\n')
				for i,k in enumerate(klist):
					l = [k.pt[0], k.pt[1], k.size, k.angle, k.class_id, k.octave, k.response, dlist[i].tostring(),'']
					f.write('\n'.join([str(e) for e in l]))
				loadBar(j, self.nbImage)
		elapsed = time.clock()
		print("Elapsed time : ", elapsed-t)
		print("Time to save one image :", (elapsed-t)/len(imageList)) 

	def loadLibrary(self, filename, dtype=np.float32):
		"""
			Load Library
		"""
		self.images = []
		print('Load images')
		with open(filename,'r') as f:
			c = time.clock()
			self.nbImage = int(f.readline())
			for i in range(self.nbImage):
				name = f.readline()
				nbDesc = int(f.readline())
				k = []
				d = []
				for i in range(nbDesc):
					x = float(f.readline())
					y = float(f.readline())
					size = float(f.readline())
					angle = float(f.readline())
					class_id = int(f.readline())
					octave = int(f.readline())
					response = float(f.readline())
					k.append(cv2.KeyPoint(x,y,size,angle, response, octave, class_id))
					d.append(np.fromstring(eval(f.readline()),dtype=dtype))
				self.images.append((name,(k,d)))
				loadBar(i, self.nbImage)
			print('time to read the library:', time.clock() - c)

	def extractVector(self, jump=1):
		vec = []
		for name,description in self.images:
			if not(description is None) and len(description) == 2:
				for desc in description[1]:
					vec.append(desc)
		return [vec[x*jump] for x in range(0,int(len(vec)/jump))]
	
