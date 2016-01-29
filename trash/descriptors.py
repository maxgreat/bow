import cv2
import numpy as np
from image2features import *
import scipy.spatial as sp
import pickle
from dataStorage import *
erreurs = {}


def closestImage(desc, key_images, key_desc, nb_el=5):
	"""
		Take an image descriptor list, and a list of image with their descriptors
	"""
	# create BFMatcher object
	from cv2 import BFMatcher, NORM_HAMMING
	nbmatches = []
	for j, img2 in enumerate(key_images):
		try:
			currentmatches = BFMatcher().knnMatch(desc, key_desc[j], k=2)
			good = []
			visited = []
			for c in currentmatches:
				if(len(c) == 2):
					m, n = c
					if m.distance < 0.75*n.distance:
						if not (m.trainIdx in visited) and not (m.queryIdx in visited):
							visited.append(m.trainIdx)
							visited.append(m.queryIdx)
							good.append([m])
			nbmatches.append((img2, len(good), good))
		except Exception:
			print 'erreur'
			print 'in image', img2
			if img2 in erreurs.keys():
				erreurs[img2] += 1
			else:
				erreurs[img2] = 1
		else:
			pass
	return sorted(nbmatches, key = lambda x: x[1])[-nb_el:]

def findClosestLabel(d, centers):
	min = sp.distance.euclidean(d, centers[0])
	num = 0
	for i,c in enumerate(centers):
		dist = sp.distance.euclidean(d, c)
		if dist < min:
			min = dist
			num = i
	return num

	
def run1():
	imlist = select_image([str(x) for x in range(1, 45)], COL_DIR, -1)
	saveData(imlist, "imlist")
	print 'Load SIFT data'
	KeyDesc = loadData('sift')
	desc = []
	for i,imdesc in enumerate(KeyDesc):
		if(imdesc != None):
			for d in imdesc:
				desc.append(d)
		else:
			print 'Image ', imlist[i], 'n a pas de decripteurs'
	desc = np.float32(desc)
	saveData(desc, 'CompleteDescriptors')
	saveVector(desc, 'SIFTVectors')
	print 'Nb descriptors:', len(desc)

def run2():
	#construction du BoW de chaque image
	desc = loadData("SIFTVectors")
	desc = np.float32([desc[i*10] for i in range(0, len(SIFTVectors)/10)])
	term_crit = (cv2.TERM_CRITERIA_EPS, 30, 0.1)
	ret, labels, centers = cv2.kmeans(desc, nbClusters, None, term_crit, 5, 0)
	saveData(ret, 'KMeansReturnValue.tmp')
	saveData(labels, 'KMeansLabels.tmp')
	saveData(centers, 'KMeansCenters')
	
def run3():
	key_bow = []
	for i, im in enumerate(imlist):
		listDesc = features[i]
		bag = [0]*1000
		for d in listDesc:
			bag[findClosestLabel(d, c)] += 1
		key_bow.append((im, bag))

	with open('bow','wb') as f:
		pickle.dump(key_bow, f)
	"""
	import pickle
	f = open('dictionary','rb')
	centers = pickle.load(f)
	f = open('bow','rb')
	key_bow = pickle.load(f)
	
	query = select_image([str(x) for x in range(1, 2)], COL_DIR+'test/', -1)
	q_k, q_d = image2descriptors(query, 'SIFT')
	query_bow = []
	for i, im in enumerate(query):
		listDesc = q_d[i]
		bag = [0]*1000
		for d in listDesc:
			bag[findClosestLabel(d, centers)] += 1
		query_bow.append((im, bag))
	
	good = 0
	for im, bow in query_bow:
		closest = key_bow[0][0]
		distance = sp.distance.euclidean(bow, key_bow[0][1])
		for kim, kbow in key_bow:
			dist = sp.distance.euclidean(bow, kbow)
			if dist < distance:
				distance = dist
				closest = kim
		if im.split('/')[-1].split('.')[0].split('-')[0] == closest.split('/')[-1].split('.')[0].split('-')[0]:
			good += 1
		print 'Closest to', im,' is ', kim
		print kbow
	print 'Precision : ', float(good)/float(len(query))
	
	"""
	"""
	good = 0
	good5 = 0
	for i, q in enumerate(query) :
		t = closestImage(q_d[i], imlist, key_d)
		imname1 = q.split('-')[0].split('/')[-1]
		imname2 = t[0][0].split('/')[-1].split('.')[0].split('-')[0]
		print 'Query ', imname1
		print imname2, ' : ', t[0][1]
		if(imname1 == imname2):
			good += 1
		found = 0
		for im, distance, desc in t:
			if im.split('/')[-1].split('.')[0].split('-')[0] == imname1:
				found = 1
		good5 += found

		img1 = cv2.imread(q,0)
		img2 = cv2.imread(t[0][0], 0)
		img3 = cv2.drawMatches(img1, q_k[0], img2, key_k[imlist.index(t[0][0])], t[0][2], None, flags=2)
		cv2.imwrite('match'+imname1+'-'+t[0][0].split('/')[-1].split('.')[0]+'.jpg',img3)
	print 'Precision:', float(good) / float(len(query))
	print 'Succes a 5:', float(good5) / float(len(query))
	print erreurs
	"""
if __name__ == "__main__":
	run()
