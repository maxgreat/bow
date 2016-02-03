//#include <QApplication>
#include <iostream>
//#include "mainwindow.h"
#include "imagelibrary.h"
#include <fstream>

static string COLLECTION_DIR = "/media/portaz/17E771D5010CDC52/CLICIDEMAX/";
static string WORKING_DIR = "/media/portaz/17E771D5010CDC52/FeaturesExtraction/";

using namespace std;

int main(/* int argc, char* argv[] */)
{
    /* Read the collection */
    cout << "Read Collection dir : " << COLLECTION_DIR << "\n";
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




    return 0;
}
