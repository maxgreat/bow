#ifndef IMAGEDESCRIPTORS_H
#define IMAGEDESCRIPTORS_H


#include <cstdio>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include "descriptor.h"
#include "imagedescriptors.h"


class ImageDescriptors
{
public:
    ImageDescriptors() {}

    ImageDescriptors(const std::string name, std::vector<Descriptor > desc, std::vector<cv::KeyPoint> kp = std::vector<cv::KeyPoint>())
    {
        imageName = name;
        descriptors = desc;
        keyPoints = kp;
    }


    ImageDescriptors(const std::string name, std::vector<std::vector<double> > desc, std::vector<cv::KeyPoint> kp = std::vector<cv::KeyPoint>())
    {
        imageName = name;
        for(size_t i = 0; i < desc.size(); i++)
        {
                descriptors.push_back(Descriptor(desc[i]));
                keyPoints.push_back(kp[i]);
        }
    }

    /**
     * @brief addDescriptor
     * @param d
     * @param kp
     * @param size
     */
    void addDescriptor(Descriptor d, cv::KeyPoint kp);

    /**
     * @brief addDescriptor
     * @param desc
     * @param kp
     */
    void addDescriptor(std::vector<double> desc, cv::KeyPoint kp);

    /**
     * @brief addDescriptor
     * @param vv
     */
    void addDescriptor(std::vector<std::vector<double> > vv, int size = 128);

    /**
     * @brief addDescriptor
     * @param vv
     */
    void addDescriptor(std::vector<Descriptor> vv);

    /**
     * @brief addDescriptor
     * @param descList
     * @param keyPointList
     */
    void addDescriptor(std::vector<std::vector<double> > descList, std::vector<cv::KeyPoint> keyPointList);

    /**
     * @brief addDescriptor
     * @param descList
     * @param keyPointList
     */
    void addDescriptor(std::vector<Descriptor> descList, std::vector<cv::KeyPoint> keyPointList);


    std::vector<Descriptor> descriptors;
    std::string imageName;
    std::vector<cv::KeyPoint> keyPoints;
};

#endif // IMAGEDESCRIPTORS_H
