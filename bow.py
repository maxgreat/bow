from imageLibrary import *
import scipy.spatial as sp
from createCluster import createCluster

HOME='../'
COL_DIR=HOME+'Collection/CLICIDEMAX/'

def ClosestCluster(d, centers):
	return centers.index(min(centers, lambda x: sp.distance.euclidean(d, x)))

def image2BOW(centroid, descriptors):
	bow = [0]*len(centroid)
	for d in descriptors:
		bow[ClosestCluster(d, centroid)] += 1
	return bow

if __name__ == "__main__":
	print('Load library')
	lib = Library("SIFT")
	lib.loadLibrary("SIFTSaved")
	print('Load ok\nextract vector')
	vec = lib.extractVector(10)
	print('Create cluster')
	centroid = createCluster(vec, 1000)
	import pickle
	print('Save cluster')
	pickle.dump(centroid, open("Centroid_SIFT_1000_10", "wb"))
	print("BOW of ", lib.images[0][0], " is", image2BOW(centroid, lib.images[0][1][1]))
