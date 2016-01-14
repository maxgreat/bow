/**
  * Image to Features
  * Extract SIFT, ORB, or Akaze features from image, using opencv
  * @author Maxime Portaz
*/

#ifndef IMAGE2FEATURES_H
#define IMAGE2FEATURES_H


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>

using namespace std;
using namespace cv;

/**
 * @brief image2SIFTFeatures
 * @param im : the input image
 * @param kp : output keypoint list
 * @param descriptors : output descriptors list (in cv::Mat)
 * @return nomber of descriptors
 */
int image2SIFTFeatures(cv::Mat im, std::vector<cv::KeyPoint> kp, cv::Mat & descriptors);


#endif // IMAGE2FEATURES_H
