import sys
from sklearn.cluster import KMeans
import numpy as np
import scipy.spatial as sp

def ClosestCluster(d, centers):
	#return centers.index(min(centers, lambda x: sp.distance.euclidean(d, x)))
	return np.argmin([sp.distance.euclidean(d, x) for x in centers])

def createCluster(vec, nbcluster=2000, nbjob=3):
	kmeans = KMeans(init='k-means++', n_clusters=nbcluster, max_iter=20, precompute_distances=True, n_jobs=nbjob)
	kmeans.fit(vec)
	return kmeans.cluster_centers_



if __name__=="__main__":
	if len(sys.argv) < 3:
		raise NameError("Usage : createCluster.py vectorFile output [nbcluster [nbjob]]")
	import pickle
	nbcluster = 2000 if len(sys.argv) == 3 else int(sys.argv[3])
	nbjob = 3 if len(sys.argv) <= 4 else int(sys.argv[4])
	with open(sys.argv[2],'w') as f:
		pickle.dump(createCluster(pickle.load(open(sys.argv[1], 'rb')), nbcluster, nbjob), f)
	
