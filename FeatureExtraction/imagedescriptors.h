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
    /**
     * @brief ImageDescriptors
     */
    ImageDescriptors() {}

    /**
     * @brief ImageDescriptors
     * @param name of the image
     * @param descriptor Type
     */
    ImageDescriptors(const std::string name, desc_type d=desc_type::orb)
    {
        imageName = name;
        image = cv::imread(name);
        vector<KeyPoint> lkp;
        if(d == desc_type::orb)
        {
            descriptorType = d;
            Ptr<ORB> o = cv::ORB::create();
            o->detectAndCompute(image,noArray(),lkp,opencvDescriptors);
        }
        else if(d == desc_type::akaze)
        {
            descriptorType = d;
            Ptr<AKAZE> o = cv::AKAZE::create();
            o->detectAndCompute(image,noArray(),lkp,opencvDescriptors);
        }
        else
        {
            cerr << "Descriptor unknown\n";
        }
        if(opencvDescriptors.elemSize() == sizeof(DescType))
        {
            for(int i = 0; i < opencvDescriptors.rows; i++){
                vector<DescType> v;
                for(int j = 0; j < opencvDescriptors.cols; j++){
                    v.push_back(opencvDescriptors.at<DescType>(i,j));
                }
                descriptors.push_back(Descriptor<DescType>(v, lkp[i]));
            }
        }
        else
        {
            cerr << "Erreur in image : " << imageName << endl;
        }

    }

    //
    // Getter / Setter
    //

    /**
     * @brief name
     * @return the name of the image
     */
    std::string& name() { return imageName; }

    /**
     * @brief operator []
     * @param i
     * @return the i-th Descritor
     */
    Descriptor<DescType>& operator[](unsigned i)
    {
        if(i >= descriptors.size())
            throw std::range_error("Too large access");
        else
           return descriptors[i];
    }

    /**
     * @brief size
     * @param i
     * @return
     */
    size_t size(int i)
    {
        return descriptors.size();
    }


    cv::Mat& getOpenCVDescriptors()
    {
        return opencvDescriptors;
    }

    /**
     * @brief getDescritors
     * @param i
     * @return the i-th in the form of a vector of vector
     */
    std::vector<std::vector<DescType> >& getDescritors(unsigned i)
    {
        std::vector<std::vector<DescType> > ldesc;
        for(size_t j= 0; j < descriptors.size(); j++)
        {
            ldesc.push_back(descriptors[i].getValue());
        }
        return ldesc;
    }


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
    cv::Mat opencvDescriptors;
    cv::Mat image;
    desc_type descriptorType;
};

#endif // IMAGEDESCRIPTORS_H
