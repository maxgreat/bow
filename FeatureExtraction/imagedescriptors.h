#ifndef IMAGEDESCRIPTORS_H
#define IMAGEDESCRIPTORS_H


#include <cstdio>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include "descriptor.h"


class ImageDescriptors
{
public:
    ImageDescriptors() {}

    ImageDescriptors(const std::string name, std::vector<Descriptor > desc)
    {
        imageName = name;
        descriptors = desc;
    }


    ImageDescriptors(const std::string name, std::vector<std::vector<double> > desc, std::vector<cv::KeyPoint> kp)
    {
        imageName = name;
        for(size_t i = 0; i < desc.size(); i++)
        {
                descriptors.push_back(Descriptor(desc[i], kp[i]));
        }
    }

    ImageDescriptors(const std::string name, cv::Mat desc, std::vector<cv::KeyPoint> kp)
    {
        imageName = name;
        for(int i = 0; i < desc.rows; i++){
            vector<double> v;
            for(int j = 0; j < desc.cols; j++){
                v.push_back(desc.at<double>(i,j));
            }
            descriptors.push_back(Descriptor(v, kp[i]));
        }
    }

    void addDescriptor(Descriptor d);

    void addDescriptor(std::vector<Descriptor>& descList);

    std::string& name() { return imageName; }

    Descriptor& operator[](unsigned i)
    {
        if(i >= descriptors.size())
            throw std::range_error("Too large access");
        else
           return descriptors[i];
    }

    unsigned size() { return descriptors.size(); }


    friend std::ostream& operator<<(std::ostream& os, const ImageDescriptors& id)
    {
        os << id.imageName << '\n';
        os << id.descriptors.size() << '\n';
        for(const auto& desc : id.descriptors)
            os << desc << '\n';
        return os;
    }

    friend std::istream& operator>>(std::istream& is, ImageDescriptors& id)
    {
        unsigned size;
        is >> id.imageName;
        is >> size;
        for(unsigned i = 0; i < size; i++)
        {
            Descriptor a;
            is >> a;
            id.descriptors.push_back(a);
        }
        return is;
    }


private:
    std::vector<Descriptor> descriptors;
    std::string imageName;
};

#endif // IMAGEDESCRIPTORS_H
