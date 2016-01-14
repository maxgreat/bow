#include <image2Features.h>

using namespace std;
using namespace cv;

int image2SIFTFeatures(cv::Mat im, std::vector<cv::KeyPoint> kp, cv::Mat & descriptors){
    //Detection of Keypoints
    FeatureDetector* fd = FeatureDetector::create("SIFT");
    fd->detect(im,kp);

    //Extraction of features
    DescriptorExtractor* de = DescriptorExtractor::create("SIFT");
    de->compute(im,kp,descriptors);

    return kp.size();
}

