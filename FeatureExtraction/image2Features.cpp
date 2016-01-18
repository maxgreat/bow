#include "image2Features.h"

using namespace std;
using namespace cv;

void images2SIFT(std::vector<string> imagesNames, std::vector<ImageDescriptors> & imagesDescriptors){
    imagesDescriptors.resize(0);
    fprintf(stderr, "Image to SIFT\n");
    for(int i = 0; i < imagesNames.size(); i++){
        vector<KeyPoint> kp;
        Mat desc;
        Mat image = imread(imagesNames[i].c_str());
        image2SIFTFeatures(image, kp, desc);
        vector<vector<double> > vlist = descriptorMat2VectorList(desc);
        ImageDescriptors id(imagesNames[i], vlist, kp);
        imagesDescriptors.push_back(id);
        loadBar(i, imagesNames.size());
    }
}

int image2SIFTFeatures(cv::Mat im, std::vector<cv::KeyPoint> & kp, cv::Mat & descriptors){
    //Detection of Keypoints
    Ptr<FeatureDetector> fd = FeatureDetector::create("ORB");
    fd->detect(im,kp);

    //Extraction of features
    Ptr<DescriptorExtractor> de = DescriptorExtractor::create("ORB");
    de->compute(im,kp,descriptors);

    return kp.size();
}


std::vector<std::string> selectImages(std::string directory, int nbImages /* =-1 */){
    vector <string> imList;
    glob_t globbuf;
    fprintf(stderr, "GLOB\n");
    glob(directory.c_str(), GLOB_TILDE, NULL, &globbuf);
    if(globbuf.gl_pathc == 0){
        fprintf(stderr, "No images corresponding to %s\n", directory.c_str());
        return imList;
    }
    if(nbImages == -1){
        for(size_t i = 0; i < globbuf.gl_pathc; i++){
            imList.push_back(globbuf.gl_pathv[i]);
        }
    }
    else{
        for(size_t i = 0; i < globbuf.gl_pathc && (int)i < nbImages; i++){
            imList.push_back(globbuf.gl_pathv[i]);
        }
    }
    return imList;
}

std::vector<std::vector<double> > descriptorMat2VectorList(cv::Mat descriptors){
    std::vector<std::vector< double> > descList;
    descList.resize(descriptors.rows);
    for(int i = 0; i < descriptors.rows; i++){
        descList[i].resize(descriptors.cols);
        for(int j = 0; j < descriptors.cols; j++){
            descList[i][j] = descriptors.at<double>(i,j);
        }
    }
    return descList;
}


