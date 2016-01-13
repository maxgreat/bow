#include <stdio.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include "DataStorage.h"
#include <iostream>
#include <glob.h>

#define COLLECTION_DIR "/home/mrim/portaz/home_dist/Collection/CLICIDE2CLEAN/"
#define SAVED_DATA "/home/mrim/portaz/home_dist/Collection/DataExtracted/"
#define NEW_COLLECTION "/home/mrim/portaz/home_dist/Collection/NEW_COLLECTION/"
#define TEST_DIR "/home/mrim/portaz/home_dist/Collection/test_simple/"

using namespace std;

int main()
{
    /*
    cv::Mat img;

    // load an image
    img = cv::Mat(400,600,CV_8UC1, cv::Scalar(128));
    cv::imshow("test image", img);
    // wait for a key
*/

    std::vector<std::vector<double> > listV;

    loadVectorList("/home/portaz/home_dist/FeaturesExtraction/SIFTVectors", listV);
    cout << "Lenth of vetor : " << listV.size() << "\n";
    cout << "Vector 1 : " << listV[0][0] << endl;
    return 0;
}
