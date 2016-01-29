import scipy.spatial as sp
import numpy as np
import os
import subprocess
import image2features

	
def save_features(feat, filename):
	"""
		Save the features dictionnary
	"""
	import pickle
	with open(filename,'wb') as f:
		pickle.dump(feat, f)
		

def load_features(filename):
	"""
		load the features dictionnary
	"""
	import pickle
	with open(filename,'rb') as f:
		feat = pickle.load(f)
	return feat
	
	

def test_distance(image_list, key_images, features):
	"""
		Compute and print distance between images
	"""
	#features = image2features.image2Features(key_images+image_list, layer=layer)
	#feat_to_test = image2features.image2Features(image_list, layer=layer)
	"""
  if len(key_features) == len(key_images):
    print 'len key features ok'
  else:
    print 'ERROR size keyfeatures'
    
  if len(feat_to_test) == len(image_list):
    print 'len features test ok'
  else:
    print 'ERROR size keyfeatures'
  """
	dist = [] #2D dictionnary
	for j,f in enumerate(image_list):
		dist.append((f, []))
		vec2 = features[f]
		for i, k in enumerate(key_images):
			vec = features[k]
			dist[j][1].append((k, sp.distance.cosine(vec, vec2)))
	return dist
		
		
		
def sort_result(res):
	"""
		Sort result
		take the result -> return a list of sorted lists
	"""
	r = []
	for i, imdist in enumerate(res):
		r.append((imdist[0], sorted(imdist[1], key = lambda x: x[1])[:5]))
	return r


def write_distance(dist, filename='distances.txt'):
	f = open(filename, 'w')
	for name,li in dist:
		f.write(name)
		for el in li:
			f.write(';'+str(el))
		f.write('\n')
	f.close()

def display_precision(tab):
	nb_bon = 0
	nb_mauvais = 0 
	for im in tab:
	  name_im = im[0].split('/')[-1].split('-')[0]
	  name_res = im[1][0][0].split('/')[-1].split('-')[0]
	  if(name_im == name_res):
	    nb_bon += 1
	  else:
		  nb_mauvais += 1
	print 'Bon :', nb_bon
	print 'Mauvais:', nb_mauvais
	print 'Precision : ', float(nb_bon) / float(nb_bon+nb_mauvais) 


def precision(tab, prec=2):
	nb_bon = 0
	nb_tot = 0 
	for im in tab:
	  name_im = im[0].split('/')[-1].split('-')[0]
	  nb_tot += 1
	  bon = False
	  for i, res in enumerate(im[1]):
		if i < prec-1:
			bon = bon or (res[0].split('/')[-1].split('-')[0] == name_im)
	  if bon:
		nb_bon += 1
	print 'Bon:', nb_bon
	print 'Precision a', prec, ':', float(nb_bon)/float(nb_tot) 

def run():
	roomlist=[str(i) for i in range(1,45)]
	imlist = image2features.select_image(roomlist, directory=image2features.COL_DIR, nb_image=-1)
	query = image2features.select_image(roomlist, image2features.COL_DIR+'test/', nb_image=-1)
	#features = image2features.image2Features(imlist+query, layer='fc7')
	#save_features(features, 'tmp.txt')
	features = load_features('tmp.txt')
	d = sort_result(test_distance(query, imlist, features))
	display_precision(d)
	precision(d)
	precision(d, 5)
	return d


if __name__=="__main__":
	run()
		
	
