#ifndef IMAGELIBRARY_C
#define IMAGELIBRARY_C

#include "imagelibrary.h"

using namespace std;

imageLibrary::imageLibrary()
{
}


void imageLibrary::addImages(const std::string directory, int nbImages /* =-1 */){

    //Read the directory for all .jpg
    vector<string> imList;
    glob_t globbuf;
    fprintf(stderr, "GLOB\n");
    glob((directory + "*.jpg").c_str(), GLOB_TILDE, NULL, &globbuf);
    glob((directory + "*.JPG").c_str(), GLOB_TILDE  | GLOB_APPEND, NULL, &globbuf);

    if(globbuf.gl_pathc == 0){
        fprintf(stderr, "No images corresponding to %s\n", directory.c_str());
        return;
    }
    fprintf(stderr, "Add images names from directory\n");
    if(nbImages == -1){
        for(size_t i = 0; i < globbuf.gl_pathc; i++){
            imList.push_back(globbuf.gl_pathv[i]);
            loadBar(i, globbuf.gl_pathc);
        }
    }
    else{
        for(size_t i = 0; i < globbuf.gl_pathc && (int)i < nbImages; i++){
            imList.push_back(globbuf.gl_pathv[i]);
        }
    }

    //Compute descriptor for each image
    addImages(imList);
}


void imageLibrary::addImages(const std::vector<string>& imNameList)
{
    vector<Mat> l;
    for(const auto& im:imNameList)
    {
        l.push_back(cv::imread(im));
    }
    vector<vector<KeyPoint> > lkp;
    vector<Mat> ldesc;
    fprintf(stderr,"Add image list\n");
    if(descriptorType == desc_type::orb){
        fprintf(stderr, "Detect keypoints\n");
        Ptr<FeatureDetector> fd = FeatureDetector::create("ORB");
        fd->detect(l,lkp);

        //Extraction of features
        fprintf(stderr, "Extract features\n");
        Ptr<DescriptorExtractor> de = DescriptorExtractor::create("ORB");
        de->compute(l,lkp,ldesc);
    }


    fprintf(stderr, "Push ImageDescriptors\n");
    for(unsigned i = 0; i < imNameList.size(); i++)
    {
        imageList.push_back(ImageDescriptors(imNameList[i],ldesc[i], lkp[i]));
        loadBar(i, imNameList.size());
    }
}


void imageLibrary::addImage(ImageDescriptors& im)
{
    imageList.push_back(im);
}


void imageLibrary::addImage(const std::string& im)
{
    if(descriptorType == desc_type::orb)
    {
        cv::Mat image = imread(im);
        std::vector<cv::KeyPoint> kp;
        cv::Mat descriptors;

        //Detection of Keypoints
        Ptr<FeatureDetector> fd = FeatureDetector::create("ORB");
        fd->detect(image,kp);

        //Extraction of features
        Ptr<DescriptorExtractor> de = DescriptorExtractor::create("ORB");
        de->compute(image,kp,descriptors);

        //Add image to the list
        imageList.push_back(ImageDescriptors(im,descriptors,kp));
    }
}


#endif

