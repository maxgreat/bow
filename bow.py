import numpy as np
import glob
import random

HOME='../'
COL_DIR=HOME+'Collection/CLICIDEMAX/'


def select_image(roomlist, directory, nb_image=-1):
	"""
		Return a list of nb_image images (default 10) 
		randomly choosen in the given directory
		imageName is the type of name to select
	"""
	print "Directory =", directory
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


def extractFeatures(imName, descType='ORB'):
	if(descType=='ORB'):
		import cv2
		im = cv2.imread(imName)
		return cv2.ORB().detectAndCompute(im, None)
	if(descType=='BRISK'):
		import cv2
		im = cv2.imread(imName)
		return cv2.BRISK().detectAndCompute(im, None)
	elif(descType=="SIFT"):
		import cv2
		im = cv2.imread(imName)
		return cv2.Features2D_create("SIFT").detectAndCompute(im, None)


def createLib(directory, nbimage=-1):
	imlist = select_image([str(x) for x in range(1, 45)], directory, nbimage)
	images = []
	for imName in imlist:
		k,d = extractFeatures(imName, 'ORB')
		if len(k) > 1 :
			images.append( (imName,(k,d)))
	return images
	
def extractVector(imageList, jump=1):
    vec = []
    for name,description in imageList :
    	if not(description is None) and len(description) == 2:
		for desc in description[1]:
		    vec.append(desc)
    return [vec[x*jump] for x in range(0,len(vec)/jump)]
	
def clusterVector(veclist, nbcluster):
	from sklearn.cluster import KMeans
	kmeans = KMeans(init='k-means++', n_clusters=nbcluster, max_iter=20, precompute_distances=True, n_jobs=-2)
	kmeans.fit(veclist)
	return kmeans.cluster_centers_
		
def saveData(data, filename):
	import pickle
	with open(filename,'wb') as f:
		pickle.dump(data, f)
		
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
	images = createLib(COL_DIR)
	
	
