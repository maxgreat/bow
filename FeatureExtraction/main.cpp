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
    imageLibrary<char> imLib = imageLibrary<char>(desc_type::orb, COLLECTION_DIR, 10);
    //cout << imLib;

    ofstream saveFile;
    saveFile.open(WORKING_DIR+"LibraryORB");
    saveFile << imLib;
    saveFile.close();
    return 0;
}
