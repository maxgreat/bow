#include <image2Features.h>


using namespace std;
using namespace cv;


void images2SIFT(std::vector<string> imagesNames, std::vector<std::vector<cv::KeyPoint> > & imagesKeypoints, std::vector<cv::Mat> & imagesDescriptors){
    imagesKeypoints.resize(0);
    imagesDescriptors.resize(0);
    int i = 0;
    for(vector<string>::iterator it = imagesNames.begin(); it != imagesNames.end(); it++){
        std::vector<cv::KeyPoint> kp;
        cv::Mat desc;
        image2SIFTFeatures(cv::imread(*it), kp, desc);
        imagesKeypoints.push_back(kp);
        imagesDescriptors.push_back(desc);
        loadBar(i, imagesNames.size());
    }
}


int image2SIFTFeatures(cv::Mat im, std::vector<cv::KeyPoint> kp, cv::Mat & descriptors){
    //Detection of Keypoints
    FeatureDetector* fd = FeatureDetector::create("SIFT");
    fd->detect(im,kp);

    //Extraction of features
    DescriptorExtractor* de = DescriptorExtractor::create("SIFT");
    de->compute(im,kp,descriptors);

    return kp.size();
}


std::vector<std::string> selectImages(std::string directory, int nbImages /* =-1 */){
    std::vector <string> imList;
    glob_t globbuf;
    glob(directory.c_str(), GLOB_DOOFFS, NULL, &globbuf);

    if(nbImages == -1){
        for(std::size_t i = 0; i < globbuf.gl_pathc; i++){
            imList.push_back(globbuf.gl_pathv[i]);
        }
    }
    else{
        for(std::size_t i = 0; i < globbuf.gl_pathc && i < nbImages; i++){
            imList.push_back(globbuf.gl_pathv[i]);
        }
    }
    return imList;
}

std::vector<std::vector< double> > descriptorMat2VectorList(cv::Mat descriptors){
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


