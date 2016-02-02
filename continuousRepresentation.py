import imageLibrary
import numpy as np

def closestImage(desc, imageLib, nb_el=5):
	"""
		Take an image descriptor list, and a list of image with their descriptors
	"""
	# create BFMatcher object
	from cv2 import BFMatcher, NORM_HAMMING
	nbmatches = []
	for j, img2 in enumerate(imageLib):
		nameComp = img2[0]
		currentmatches = BFMatcher().knnMatch(queryDescriptors=desc, img2[1][1], k=2)
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
	return sorted(nbmatches, key = lambda x: x[1])[-nb_el:]
	
def closestImageSimple(desc, imageLib, nb_el=5):
	"""
		Take an image descriptor list, and a list of image with their descriptors
	"""
	# create BFMatcher object
	from cv2 import BFMatcher, NORM_HAMMING
	nbmatches = []
	matcher = BFMatcher(NORM_HAMMING, crossCheck=True)
	for j, img2 in enumerate(imageLib):
		nameComp = img2[0]
		currentmatches = matcher.match(desc, img2[1][1])
		#matches = sorted(currentmatches, key = lambda x:x.distance)
		nbmatches.append((img2, len(currentmatches), currentmatches))
	return sorted(nbmatches, key = lambda x: x[1])[-nb_el:]
	
	
if __name__=='__main__':
	lib = Library()
	lib.loadLibrary('ORBSaved', np.uint8)
	#read the queries
	imList = select_image([i for i in range(1,42)], '/media/portaz/17E771D5010CDC52/CLICIDEMAX/test/', nb_image=-1)
	for imName in imList:
		img = cv2.imread(imName)
	
