from imageLibrary import *
import scipy.spatial as sp
from cluster import createCluster, ClosestCluster

HOME='../'
COL_DIR=HOME+'Collection/CLICIDEMAX/'


class BagOfWord:
	def __init__(self, centroid, descriptors):
		self.bow = [0]*len(centroid)
		for d in descriptors:
			self.bow[ClosestCluster(d, centroid)] += 1

	def __getitem__(self, i):
		return self.bow[i]
	
	def __len__(self):
		return len(self.bow)

	def __norm__(self):
		return norm(self.bow)
	
	def __sub__(self, a):
		return [self[i] - a[i] for i in range(len(self))]
	
	def __add__(self, a):
		return [self[i] + a[i] for i in range(len(self))]

	def __str__(self):
		s = '[ '
		for i in self:
			s += str(i) + ' '
		return s+']'

class ImageDictionary:
	def __init__(self):
		self.images=[]
		
	def __getitem__(self, i):
		return self.images[i]
		
	def __len__(self):
		return len(self.images)
		
	def append(self, name, bow):
		self.images.append((name, bow))
		
	def top5Closest(self, bow):
		closest=sorted([(n, sp.distance.cosine(bow,b)) for (n,b) in self.images], key=lambda x:x[1])
		return closest[0:5]
	
	def __str__(self):
		s = ''
		for i in self:
			s += str(i[0]) + ' : ' + str(i[1]) + '\n'
		return s 
	
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
