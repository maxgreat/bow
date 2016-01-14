#include <cstdio>
#include "DataStorage.h"
#include "image2Features.h"
#include <iostream>
#include <ctime>
#include <glob.h>
#include <drawing.h>
#include <vector>

static const string COLLECTION_DIR = "/media/portaz/17E771D5010CDC52/CLICIDEMAX/";
static const string WORKING_DIR = "/media/portaz/17E771D5010CDC52/FeaturesExtraction/";

using namespace std;

int main()
{
    /* Read the collection */
    vector<string> imageList = selectImages(COLLECTION_DIR+"*.jpg");

    std::vector<std::vector<cv::KeyPoint> > imagesKeypoints;
    std::vector<cv::Mat> imagesDescriptors;
    images2SIFT(imageList,imagesKeypoints, imagesDescriptors);
    std::vector<std::vector<double> > listV;

    int t = clock();
    storeVectorList("/home/portaz/home_dist/FeaturesExtraction/SIFTVectors", listV);
    int t2 = clock();
    fprintf(stderr, "Elapsed time = %f\n", (t2-t)/(double)CLOCKS_PER_SEC);
    cout << "Lenth of vetor : " << listV.size() << "\n";
    cout << "Vector 1 : " << listV[0][0] << endl;
    return  0;
}
