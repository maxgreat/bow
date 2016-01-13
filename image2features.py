import glob
import random
import os
import subprocess

#define every path needed to cool caffe
HOME='../'
COL_DIR=HOME+'Collection/CLICIDEMAX/'
modeldir=HOME+"caffe_models/vgg/"
extractdir=HOME+"FeaturesExtraction/DeepLearning/"
caffe=HOME+"caffe/caffe_cpu/build/"
LIB_PATH='/usr/local/cuda/lib64:/usr/local/lib:/opt/intel/mkl/lib/intel64'

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


def read_features(namelist, filename):
	"""
		for each name in namelist, read the corresponding feature in the file filename
		return value:
			{image name, feature array}
		
		Namelist and the features in the file have to be in the same order and must have the same size !
		!! More likely to use image2Features !!
	"""
	features = {}
	with open(filename) as f:
		for i, l in enumerate(f.readlines()):
			features[namelist[i]] = [float(x) for x in l.split(' ')[0:-1]]
	return features


def image2descriptors(imlist, descriptor='ORB'):
	"""
		For each image in the imlist list
		extract the given descriptor (ORB and SIFT supported)
		
		Return the lists : [keypoint], [descriptor]
	"""
	from cv2 import imread
	desc = []
	key = []
	if(descriptor=='ORB'):
		from cv2 import ORB_create
		for imname in imlist:
			im = imread(imname)
			k, d = ORB_create().detectAndCompute(im, None)
			desc.append(d)
			key.append(k)
	if(descriptor=='BRISK'):
		from cv2 import BRISK_create
		for imname in imlist:
			im = imread(imname)
			k, d = BRISK_create().detectAndCompute(im, None)
			desc.append(d)
			key.append(k)
	elif(descriptor=="SIFT"):
		from cv2.xfeatures2d import SIFT_create
		for imname in imlist:
			im = imread(imname)
			k, d = SIFT_create().detectAndCompute(im, None)
			desc.append(d)
			key.append(k)
	else:
		print 'Desc is not equal to ORB or to SIFT'
	print 'bordel'
	return key, desc
	
def image2Features(imagelist, destination=extractdir+'vgg.features', layer='prob'):
	"""
		Given a imagelist, call caffe with the vgg model trained on imageNet
		return the image and the corresponding features
	"""
	exe=caffe+'tools/extract_features_dims3.bin'
	model=modeldir+'VGG_ILSVRC_19_layers.caffemodel'
	proto=modeldir+'vgg_proto.txt'
	nbimages=str(len(imagelist))
	print "Call caffe with", nbimages, " images" 
	
	for i in glob.glob(extractdir+"input_vgg.txt"):
	  subprocess.call(['rm', '-f', i])
	
	with open(extractdir+"input_vgg.txt", "w") as f:
		for im in imagelist:
			f.write(im+' 0\n')
	
	os.environ['LD_LIBRARY_PATH'] = LIB_PATH
	
	for i in glob.glob(destination):
	  subprocess.call(['rm', '-f', i])
	fout = open("caffe_out.txt", "w")
	subprocess.call([exe, model, proto, layer, destination, nbimages, '25', 'GPU', '0'], stdout=fout, stderr=fout)
	
	return read_features(imagelist, destination)
	
