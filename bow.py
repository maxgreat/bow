from imageLibrary import *
import scipy.spatial as sp

HOME='../'
COL_DIR=HOME+'Collection/CLICIDEMAX/'

def clusterVector(veclist, nbcluster):
	from sklearn.cluster import KMeans
	kmeans = KMeans(init='k-means++', n_clusters=nbcluster, max_iter=20, precompute_distances=True, n_jobs=3)
	kmeans.fit(veclist)
	return kmeans.cluster_centers_

def ClosestCluster(d, centers):
	return centers.index(min(centers, lambda x: sp.distance.euclidean(d, x)))

def image2BOW(centroid, descriptors):
	bow = [0]*len(centroid)
	for d in descriptors:
		bow[ClosestCluster(d, centroid)] += 1
	return bow

if __name__ == "__main__":
	lib = imageLibrary.Library("SIFT")
	lib.loadLibrary("SIFTSaved")
	vec = lib.extractVector(10)
	
	
