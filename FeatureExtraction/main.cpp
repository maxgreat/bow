//#include <QApplication>
#include <cstdio>
#include "DataStorage.h"
#include "image2Features.h"
#include "descriptor.h"
#include <iostream>
#include <vector>
//#include "mainwindow.h"
#include "imagedescriptors.h"

static string COLLECTION_DIR = "/media/portaz/17E771D5010CDC52/CLICIDEMAX/";
static string WORKING_DIR = "/media/portaz/17E771D5010CDC52/FeaturesExtraction/";

using namespace std;

int main(/* int argc, char* argv[] */)
{
/*    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
*/
    /* Read the collection */
   /* cout << "Read Collection dir : " << COLLECTION_DIR << "\n";
    vector<string> imageList = selectImages(COLLECTION_DIR+"*.JPG");
*/
    /* Extract Keypoints and Descriptors */
/*    std::vector<ImageDescriptors> imagesDescriptors;
    cout << "Extract SIFT on each Image\nWe have " << imageList.size() << " images\n";
    images2SIFT(imageList, imagesDescriptors);
    cout << "We extracted "<< imagesDescriptors.size() << " descriptors.\nSave image list\n";
    storeName(WORKING_DIR+"ImageNameList", imageList);
    cout << "Save Descriptors\n";
    storeVectorList(WORKING_DIR+"SIFTVectorsCPP", imagesDescriptors);
  */
    vector<string> imageList;
    loadName(WORKING_DIR+"ImageNameList", imageList);
    cout << "Name list size :" << imageList.size();
    //loadVectorList
    return 0;
}
