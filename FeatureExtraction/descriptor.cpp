#include "descriptor.h"

using namespace std;

/* **********************************************************************
 * Descriptor functions
 * ********************************************************************** */
template<typename T>
Descriptor<T>::Descriptor(int size /* = 128 */)
{
    descriptorSize = size;
    value.resize(descriptorSize);
}

template<typename T>
Descriptor<T>::Descriptor(std::vector<T> vd, int size /* = 128 */)
{
    descriptorSize = size;
    if(vd.size() == 128){
        value = vd;
    }
    else{
        fprintf(stderr, "Error vector size\n");
        value.resize(descriptorSize);
    }
}


/* **********************************************************************
 * ImageDescriptors functions
 * ********************************************************************** */
template<typename T>
void ImageDescriptors<T>::addDescriptor(Descriptor<T> d, cv::KeyPoint kp, int size /* =128 */)
{
    descriptors.push_back(d, size);
    keyPoints = kp;
}

template<typename T>
void ImageDescriptors<T>::addDescriptor(std::vector<T> desc, cv::KeyPoint kp)
{
    descriptors.push_back(Descriptor<T>(desc), desc.size());
    keyPoints.push_back(kp);
}

template<typename T>
void ImageDescriptors<T>::addDescriptor(std::vector<std::vector<T> > vv)
{
    for(size_t i = 0; i< vv.size(); i++)
    {
        descriptors.push_back(Descriptor<T>(vv[i]), vv.size());
        keyPoints.push_back(cv::KeyPoint());
    }
}

template<typename T>
void ImageDescriptors<T>::addDescriptor(std::vector<Descriptor<T> > vv)
{
    for(size_t i = 0; i< vv.size(); i++)
    {
        descriptors.push_back(Descriptor<T>(vv[i]), vv.size());
        keyPoints.push_back(cv::KeyPoint());
    }
}

template<typename T>
void ImageDescriptors<T>::addDescriptor(std::vector<std::vector<T> > descList, std::vector<cv::KeyPoint> keyPointList)
{
    if(descList.size() == keyPoints.size())
    {
        for(size_t i = 0; i < descList.size(); i++)
        {
                descriptors.push_back(Descriptor<T>(descList[i]));
                keyPoints.push_back(keyPointList[i]);
        }

    } else
    {
        fprintf(stderr, "Error : descriptor list and keypoint list do not have the same size\n");
    }
}

template<typename T>
void ImageDescriptors<T>::addDescriptor(std::vector<Descriptor<T> > descList, std::vector<cv::KeyPoint> keyPointList){
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
