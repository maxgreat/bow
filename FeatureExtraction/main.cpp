#include <stdio.h>
#include <opencv2/highgui/highgui.hpp>
#include "DataStorage.h"
#include "image2Features.h"
#include <iostream>
#include <ctime>
#include <glob.h>

static const string COLLECTION_DIR = "/media/portaz/17E771D5010CDC52/CLICIDEMAX/";
static const string WORKING_DIR = "/media/portaz/17E771D5010CDC52/FeaturesExtraction/";

using namespace std;

/**
 * @brief selectImages
 * @param directory : directory where the images are
 * @param nb_image : nb images to take
 * @return list of images
 */
std::vector<std::string> selectImages(std::string directory, int nbImages=-1){
    std::vector <char *> imList;
    glob_t globbuf;
    glob(directory, GLOB_DOOFFS, NULL, &globbuf);

    if(nbImages == -1){
        for(std::size_t i = 0; i < globbuf.gl_pathc; i++){
            imList.pop_back(globbuf.gl_pathv[i]);
        }
    }
    else{
        for(std::size_t i = 0; i < globbuf.gl_pathc && i < nbImages; i++){
            imList.pop_back(globbuf.gl_pathv[i]);
        }
    }
    return imList;
}



int main()
{
    /*
    cv::Mat img;

    // load an image
    img = cv::Mat(400,600,CV_8UC1, cv::Scalar(128));
    cv::imshow("test image", img);
    // wait for a key
*/

    /* Read the collection */
    vector<string> imageList = selectImages(COLLECTION_DIR+"*.jpg");

    std::vector<std::vector<double> > listV;
    int t = clock();
    loadVectorList("/home/portaz/home_dist/FeaturesExtraction/SIFTVectors", listV);
    int t2 = clock();
    fprintf(stderr, "Elapsed time = %f\n", (t2-t)/(double)CLOCKS_PER_SEC);
    cout << "Lenth of vetor : " << listV.size() << "\n";
    cout << "Vector 1 : " << listV[0][0] << endl;
    return 0;
}
