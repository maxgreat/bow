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
 * @brief images2SIFT
 * @param imagesNames input list of image
 * @param ImagesKeypoints output list of keypoints list for each image
 * @param ImagesDescriptors output list of descriptors for each image
 */
void images2SIFT(std::vector<string> imagesNames, std::vector<std::vector<cv::KeyPoint> > & imagesKeypoints, std::vector<cv::Mat> & imagesDescriptors);


/**
 * @brief image2SIFTFeatures
 * @param im : the input image
 * @param kp : output keypoint list
 * @param descriptors : output descriptors list (in cv::Mat)
 * @return nomber of descriptors
 */
int image2SIFTFeatures(cv::Mat im, std::vector<cv::KeyPoint> kp, cv::Mat & descriptors);



/**
 * @brief selectImages
 * @param directory : directory where the images are
 * @param nb_image : nb images to take
 * @return list of images
 */
std::vector<std::string> selectImages(std::string directory, int nbImages=-1);

#endif // IMAGE2FEATURES_H
