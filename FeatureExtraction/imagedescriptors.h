#ifndef IMAGEDESCRIPTORS_H
#define IMAGEDESCRIPTORS_H


#include <cstdio>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "descriptor.h"

using namespace std;

template<typename DescType>
class ImageDescriptors
{
public:
    ImageDescriptors() {}

    ImageDescriptors(const std::string name, desc_type d=desc_type::orb)
    {
        cerr << "Create Image Descriptor with image " << name << '\n';
        imageName = name;
        image = cv::imread(name);
        vector<KeyPoint> lkp;
        Mat ldesc;
        if(d == desc_type::orb)
        {
            cerr << "Compute orb\n";
            descriptorType = d;
            Ptr<ORB> o = cv::ORB::create();
            o->detectAndCompute(image,noArray(),lkp,ldesc);
        }
        else
        {
            cerr << "Descriptor unknown\n";
        }
        if(ldesc.elemSize() == sizeof(DescType))
        {
            for(int i = 0; i < ldesc.rows; i++){
                vector<DescType> v;
                for(int j = 0; j < ldesc.cols; j++){
                    v.push_back(ldesc.at<DescType>(i,j));
                }
                descriptors.push_back(Descriptor<DescType>(v, lkp[i]));
            }
        }
        else
        {
            fprintf(stderr, "Error, descriptor size unkown : %d\n", (int)ldesc.elemSize());
            exit(-1);
        }

    }



    //
    // Getter / Setter
    //

    std::string& name() { return imageName; }

    Descriptor<DescType>& operator[](unsigned i)
    {
        if(i >= descriptors.size())
            throw std::range_error("Too large access");
        else
           return descriptors[i];
    }

    unsigned size() { return descriptors.size(); }


    //
    // Printer
    //

    friend std::ostream& operator<<(std::ostream& os, const ImageDescriptors& id)
    {
        os << id.imageName << '\n';
        os << id.descriptors.size() << '\n';
        for(const auto& desc : id.descriptors)
            os << '\t' << desc << '\n';
        return os;
    }

    friend std::istream& operator>>(std::istream& is, ImageDescriptors& id)
    {
        unsigned size;
        is >> id.imageName;
        is >> size;
        for(unsigned i = 0; i < size; i++)
        {
            Descriptor<DescType> a;
            is >> a;
            id.descriptors.push_back(a);
        }
        return is;
    }


private:
    std::vector<Descriptor<DescType> > descriptors;
    std::string imageName;
    cv::Mat image;
    desc_type descriptorType;
};

#endif // IMAGEDESCRIPTORS_H
