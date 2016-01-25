import numpy as np
import glob
import random
import cv2
if int(cv2.__version__.split('.')[0]) != 3:
	print("Error, OpenCV 3 needed")
	raise Exception("OpenCV 3 needed")

HOME='../'
COL_DIR=HOME+'Collection/CLICIDEMAX/'


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

def createLib(directory, descType='ORB', nbimage=-1):
	if(descType=='ORB'):
		import cv2
		extractor = cv2.ORB_create()
	elif(descType=='BRISK'):
		import cv2
		extractor = cv2.BRISK_create()
	elif(descType=='AKAZE'):
		import cv2
		extractor = cv2.AKAZE_create()
	elif(descType=="SIFT"):
		import cv2
		extractor=cv2.xfeatures2d.SIFT_create()
	else:
		print("Descriptor not found")
		return
	imlist = select_image([str(x) for x in range(1, 45)], directory, nbimage)
	print(str(len(imlist))+' images selected')
	images = []
	for imName in imlist:
		print('Add image'+ imName+ ' to the library')
		k,d = extractFeatures(imName, extractor)
		if len(k) > 1 :
			images.append( (imName,(k,d)))
	return images
	
def extractVector(imageList, jump=1):
    vec = []
    for name,description in imageList :
    	if not(description is None) and len(description) == 2:
    		for desc in description[1]:
    			vec.append(desc)
    return [vec[x*jump] for x in range(0,int(len(vec)/jump))]
	
def clusterVector(veclist, nbcluster):
	from sklearn.cluster import KMeans
	kmeans = KMeans(init='k-means++', n_clusters=nbcluster, max_iter=20, precompute_distances=True, n_jobs=3)
	kmeans.fit(veclist)
	return kmeans.cluster_centers_
		
def saveData(data, filename):
	import pickle
	with open(filename,'wb') as f:
		pickle.dump(data, f)

def saveImages(imageList, filename):
    with open(filename,'w') as f:
        f.write(str(len(imageList)) + '\n')
        for name, (klist, dlist) in imageList:
            f.write(name+'\n'+str(len(klist)) + '\n')
            for i in range(0, len(klist)):
                f.write(str(klist[i].pt)+'\n'+str(klist[i].size)+'\n'+str(klist[i].angle)+'\n'+str(klist[i].class_id)+'\n'+str(klist[i].octave)+'\n'+str(klist[i].response)+'\n') 
                f.write(str(dlist[i].tostring())+'\n')
			

def loadData(filename):
	"""
		load the data
	"""
	if(fileExists(filename)):
		with open(filename,'rb') as f:
			feat = pickle.load(f)
		return feat
	else:
		raise NameError(filename)

if __name__ == "__main__":
	images = bow.createLib('/media/portaz/17E771D5010CDC52/CLICIDEMAX/', descType ='SIFT', nbimage=10)
	extractVector(images, 10)
	
	
