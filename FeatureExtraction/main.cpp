#include <QApplication>
#include <cstdio>
#include "DataStorage.h"
#include "image2Features.h"
#include "descriptor.h"
#include <iostream>
#include <vector>
#include "mainwindow.h"
#include "imagedescriptors.h"

static const string COLLECTION_DIR = "/media/portaz/17E771D5010CDC52/CLICIDEMAX/";
static const string WORKING_DIR = "/media/portaz/17E771D5010CDC52/FeaturesExtraction/";

using namespace std;

int main(int argc, char* argv[])
{
/*    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
*/
    /* Read the collection */
    cout << "Read Collection dir : " << COLLECTION_DIR << "\n";
    vector<string> imageList = selectImages(COLLECTION_DIR+"*.jpg");

    /* Extract Keypoints and Descriptors */
    std::vector<ImageDescriptors> imagesDescriptors;
    cout << "Extract SIFT on each Image\n";
    images2SIFT(imageList, imagesDescriptors);
    cout << "Save Descriptors\n";
    storeVectorList("SIFTVectorsCPP", imagesDescriptors);
    cout << "Save image list\n";
    storeName("ImageNameList", imageList);

}
