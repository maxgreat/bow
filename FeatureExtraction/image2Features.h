#ifndef IMAGE2FEATURES_H
#define IMAGE2FEATURES_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>

using namespace std;
using namespace cv;

int image2Features(cv::Mat im, vector<KeyPoint> kp, cv::Mat & descriptors){
    //Detection of Keypoints
    FeatureDetector fd = FeatureDetector::create("SIFT");
    fd.detect(im,kp);

    //Extraction of features
    DescriptorExtractor de = DescriptorExtractor::create("SIFT");
    de.compute(im,kp,descriptors);

    return kp.size();
}




#endif // IMAGE2FEATURES_H
