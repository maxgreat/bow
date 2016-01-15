/**
 * Handle image descriptor generated with openCV
 * @author Maxime Portaz
 */

#ifndef DESCRIPTOR_H
#define DESCRIPTOR_H

#include <cstdio>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>

/**
 * Class Descriptor
 */
template <typename T>
class Descriptor
{
public:
    Descriptor(int size = 128);

    Descriptor(std::vector<T> vd, int size = 128);

    int descriptorSize;
    std::vector<T> value;
};

/**
 * Class ImageDescriptors
 * Store name, keypoints and descriptors for one image
 */
template <typename T>
class ImageDescriptors
{
public:
    ImageDescriptors();

    ImageDescriptors(const std::string name, std::vector<Descriptor<T> > desc, std::vector<cv::KeyPoint> kp = std::vector<cv::KeyPoint>())
    {
        imageName = name;
        descriptors = desc;
        keyPoints = kp;
    }

    ImageDescriptors(const std::string name, std::vector<std::vector<T> > desc, std::vector<cv::KeyPoint> kp = std::vector<cv::KeyPoint>())
    {
        imageName = name;
        keyPoints = kp;
        addDescriptor(desc);
    }

    void addDescriptor(Descriptor<T> d, cv::KeyPoint kp, int size=128);

    void addDescriptor(std::vector<T> desc, cv::KeyPoint kp);

    void addDescriptor(std::vector<std::vector<T> > vv);

    void addDescriptor(std::vector<Descriptor<T> > vv);

    void addDescriptor(std::vector<std::vector<T> > descList, std::vector<cv::KeyPoint> keyPointList);

    void addDescriptor(std::vector<Descriptor<T> > descList, std::vector<cv::KeyPoint> keyPointList);


    std::vector<Descriptor<T> > descriptors;
    std::string imageName;
    std::vector<cv::KeyPoint> keyPoints;
};

#endif // DESCRIPTOR_H
