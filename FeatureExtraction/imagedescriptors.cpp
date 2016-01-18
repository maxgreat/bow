#include "imagedescriptors.h"

void ImageDescriptors::addDescriptor(Descriptor d, cv::KeyPoint kp)
{
    descriptors.push_back(d);
    keyPoints.push_back(kp);
}

void ImageDescriptors::addDescriptor(std::vector<double> desc, cv::KeyPoint kp)
{
    descriptors.push_back(Descriptor(desc));
    keyPoints.push_back(kp);
}


void ImageDescriptors::addDescriptor(std::vector<std::vector<double> > vv, int size /* = 128 */)
{
    for(size_t i = 0; i< vv.size(); i++)
    {
        descriptors.push_back(Descriptor(vv[i], size));
        keyPoints.push_back(cv::KeyPoint());
    }
}

void ImageDescriptors::addDescriptor(std::vector<Descriptor> vv)
{
    for(size_t i = 0; i< vv.size(); i++)
    {
        descriptors.push_back(vv[i]);
        keyPoints.push_back(cv::KeyPoint());
    }
}


void ImageDescriptors::addDescriptor(std::vector<std::vector<double> > descList, std::vector<cv::KeyPoint> keyPointList)
{
    if(descList.size() == keyPoints.size())
    {
        for(size_t i = 0; i < descList.size(); i++)
        {
                descriptors.push_back(Descriptor(descList[i]));
                keyPoints.push_back(keyPointList[i]);
        }

    } else
    {
        fprintf(stderr, "Error : descriptor list and keypoint list do not have the same size\n");
    }
}

void ImageDescriptors::addDescriptor(std::vector<Descriptor> descList, std::vector<cv::KeyPoint> keyPointList){
    if(descList.size() == keyPoints.size())
    {
        for(size_t i = 0; i < descList.size(); i++)
        {
                descriptors.push_back(descList[i]);
                keyPoints.push_back(keyPointList[i]);
        }

    } else
    {
        fprintf(stderr, "Error : descriptor list and keypoint list do not have the same size\n");
    }
}
