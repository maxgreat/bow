//#include <QApplication>
#include <iostream>
#include <vector>
//#include "mainwindow.h"
#include "imagelibrary.h"

static string COLLECTION_DIR = "/media/portaz/17E771D5010CDC52/CLICIDEMAX/";
static string WORKING_DIR = "/media/portaz/17E771D5010CDC52/FeaturesExtraction/";

using namespace std;

int main(/* int argc, char* argv[] */)
{
    /* Read the collection */
    cout << "Read Collection dir : " << COLLECTION_DIR << "\n";
    imageLibrary imLib;
    imLib.addImages(COLLECTION_DIR);

    /* Extract Keypoints and Descriptors */
/*    std::vector<ImageDescriptors> imagesDescriptors;
    cout << "Extract SIFT on each Image\nWe have " << imageList.size() << " images\n";
    images2SIFT(imageList, imagesDescriptors);
    cout << "We extracted "<< imagesDescriptors.size() << " descriptors.\nSave image list\n";
    storeName(WORKING_DIR+"ImageNameList", imageList);
    cout << "Save Descriptors\n";
    storeVectorList(WORKING_DIR+"SIFTVectorsCPP", imagesDescriptors);
  */
    char a;
    cin >> a;
    while(a != 'q')
            cin>>a;
    return 0;
}
