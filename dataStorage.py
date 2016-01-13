import sys
if sys.version_info.major == 3:
	import pickle
else:
	import cPickle as pickle


def saveData(data, filename):
	"""
		Save the data
	"""
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

def fileExists(fname):
	"""
		Test if file exists and is a file
	"""
	import os.path	
	return os.path.isfile(fname)
	
def saveVector(vecList, filename):
	"""
		Save a file, with the number of vector and the size of the vectors
	"""
	assert (len(vecList) > 0),"vecList must be a list of vector"
	assert (len(vecList[0]) > 0),"vecList must contain vectors"
	with open(filename, "w") as f:
		f.write(str(len(vecList)) + ' ' + str(len(vecList[0])) + '\n')
		for v in vecList:
			for i in v:
				f.write(str(i) + ' ')
			f.write('\n')
		
