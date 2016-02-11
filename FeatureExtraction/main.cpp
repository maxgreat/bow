//#include <QApplication>
#include <iostream>
//#include "mainwindow.h"
#include "imagelibrary.h"
#include <fstream>
#include <glob.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
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

    BagOfWord bow;

    glob_t globbuf;
    glob((COLLECTION_DIR + "*.jpg").c_str(), GLOB_TILDE, NULL, &globbuf);
    glob((COLLECTION_DIR + "*.JPG").c_str(), GLOB_TILDE  | GLOB_APPEND, NULL, &globbuf);

    cerr << "Add image to the lib" << endl;
    for(size_t i = 0; i < globbuf.gl_pathc; i++){
        loadBar(i, globbuf.gl_pathc-1);
        bow.AddImage(globbuf.gl_pathv[i], 16);
        //cv::waitKey();
    }
    bow.saveDesc(WORKING_DIR+"SIFT_DENSE_50", 50);
    bow.saveDesc(WORKING_DIR+"SIFT_DENSE_20", 20);
    bow.saveDesc(WORKING_DIR+"SIFT_DENSE_10", 10);
    bow.saveDesc(WORKING_DIR+"SIFT_DENSE_5", 5);
    bow.saveDesc(WORKING_DIR+"SIFT_DENSE_1", 1);

//    BagOfWord bow;
//    bow.loadCluster(WORKING_DIR+"/centers_2000_1_random");
////    cout << "BOW:";
////    for(auto& i : b )
////        cout << i << " ";
////    cout << '\n' << endl;
//    cv::Mat im;
//    vector<vector<int> > vecBow;
//    for(size_t i = 0; i < globbuf.gl_pathc && i < 20; i++)
//    {
//        im = cv::imread(globbuf.gl_pathv[i]);
//        vecBow.push_back(bow.ImageToBOW(im,16,true));
//        cv::waitKey(0);
//    }
//    cout << "Compute histogram" << endl;
//    //Compute historgramme:
//    int hist[2000];
//    for(int i = 0; i < 2000; i++)
//        hist[i] = 0;
//    unsigned long long int somme = 0;
//    for(auto& b:vecBow)
//    {
//        for(int i = 0; i < 2000; i++)
//        {
//            hist[i] += b[i];
//            somme += b[i];
//        }
//    }

//    cout << "Histogramme :" << endl;
//    for(int i = 0; i < 2000 ; i++)
//    {
//        cout << (int)(hist[i]*100.0/somme) << " ";
//    }
//    cout << endl << flush;
    return 0;
}



