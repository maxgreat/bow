/**
 * @author Maxime Portaz
 */
#ifndef DESCRIPTOR_H
#define DESCRIPTOR_H

#include <cstdio>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include "drawing.h"


/**
 * Class Descriptor - represent a list of <double> with the keypoint associated
 */
class Descriptor
{
public:
    Descriptor() {}
    Descriptor(int size);

    Descriptor(std::vector<double> vd, cv::KeyPoint kp);

    double& operator[](const unsigned i);

    cv::KeyPoint& getKeyPoint() { return keyPoint; }

    friend std::ostream& operator<<(std::ostream& os, const Descriptor& d)
    {
        if(d.value.size() == 0)
            return os;
        os << d.value.size() << '\n';
        printKeyPoint(os,d.keyPoint);
        os << '\n';
        for(const auto& val : d.value)
            os << val << '\n';
        return os;
    }

    friend std::istream& operator<<(std::istream& is, Descriptor& d)
    {
        unsigned size;
        is >> size;
        d.keyPoint = readKeyPoint(is);
        for(unsigned i = 0; i < size; i++)
        {
            double a;
            is >> a;
            d.value.push_back(a);
        }
        return is;
    }


    unsigned size(){ return value.size(); }

private:
    std::vector<double> value;
    cv::KeyPoint keyPoint;
};



#endif // DESCRIPTOR_H
