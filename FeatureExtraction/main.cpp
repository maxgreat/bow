//#include <QApplication>
#include <iostream>
//#include "mainwindow.h"
#include "imagelibrary.h"
#include <fstream>
#include <glob.h>
#include <opencv2/core/core.hpp>
#include "bagofword.h"

static string COLLECTION_DIR = "/media/portaz/17E771D5010CDC52/CLICIDEMAX/";
static string WORKING_DIR = "/media/portaz/17E771D5010CDC52/FeaturesExtraction/";

using namespace std;
using namespace cv;

int main(/* int argc, char* argv[] */)
{
    /* Read the collection */
/*    cout << "Read Collection dir : " << COLLECTION_DIR << "\n";
//    imageLibrary<unsigned char> imLib(desc_type::akaze, COLLECTION_DIR, -1);
    //cout << imLib;
      imageLibrary<unsigned char> imLib(desc_type::akaze);
//    ofstream saveFile;
//    saveFile.open(WORKING_DIR+"LibraryAKAZE");
//    saveFile << imLib;
//    saveFile.close();


    ifstream loadFile(WORKING_DIR+"LibraryAKAZE");
    loadFile >> imLib;
    loadFile.close();


//    BFMatcher matcher(NORM_HAMMING);
//    matcher.knnMatch(desc1, desc2, nn_matches, 2);


    glob_t globbuf;
    glob((COLLECTION_DIR+"test/" + "*.jpg").c_str(), GLOB_TILDE, NULL, &globbuf);
    glob((COLLECTION_DIR+"test/" + "*.JPG").c_str(), GLOB_TILDE  | GLOB_APPEND, NULL, &globbuf);

    cv::Mat im;
    cv::Mat desc1;
    vector<vector<cv::DMatch> > nnmatches;
    Ptr<AKAZE> akaze = AKAZE::create();
    for(size_t i = 0; i < globbuf.gl_pathc; i++){
        im = cv::imread(globbuf.gl_pathv[i]);
        for(size_t i = 0 ; i < imLib.size(); i++)
        {
            desc1 = imLib[i].getOpenCVDescriptors();

        }
    }
  */

//    BagOfWord bow;

    glob_t globbuf;
    glob((COLLECTION_DIR + "*.jpg").c_str(), GLOB_TILDE, NULL, &globbuf);
    glob((COLLECTION_DIR + "*.JPG").c_str(), GLOB_TILDE  | GLOB_APPEND, NULL, &globbuf);

//    cerr << "Add image to the lib" << endl;
//    for(size_t i = 0; i < globbuf.gl_pathc; i++){
//        loadBar(i, globbuf.gl_pathc);
//        bow.AddImage(globbuf.gl_pathv[i]);
//    }
//    bow.saveDesc(WORKING_DIR+"SIFT_10", 10);
//    bow.saveDesc(WORKING_DIR+"SIFT_5", 5);
//    bow.saveDesc(WORKING_DIR+"SIFT_1", 1);

    BagOfWord bow;
    bow.loadCluster(WORKING_DIR+"centers_2000_5");
    cv::Mat image = imread(COLLECTION_DIR+"32A-0.JPG");
    vector<int> b = bow.ImageToBOW(image);
    cout << "BOW:";
    for(auto& i : b )
        cout << i << " ";
    cout << '\n' << endl;
    return 0;
}



