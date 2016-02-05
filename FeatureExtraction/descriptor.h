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


enum class desc_type {orb, akaze}; /* TODO : add other descriptors */

std::istream& operator>>(std::istream& is, desc_type& value);

std::ostream& operator<<(std::ostream& os, const desc_type value);

/**
 * Class Descriptor - represent a list of <double> with the keypoint associated
 */
template<typename DescSize>
class Descriptor
{
public:
    /**
     * @brief Descriptor
     */
    Descriptor() {}

    /**
     * @brief Descriptor
     * @param size
     */
    Descriptor(int size)
    {
        value.resize(size);
    }

    /**
     * @brief Descriptor
     * @param vd
     * @param kp
     */
    Descriptor(std::vector<DescSize> vd, cv::KeyPoint kp = cv::KeyPoint())
    {
        if(vd.size() > 0)
        {
            keyPoint = kp;
            value = vd;
        }
    }

    /**
     * @brief operator []
     * @param i
     * @return
     */
    DescSize& operator[](const unsigned i)
    {
        if(i >= value.size())
            throw std::range_error("Out of range");
        else
            return value[i];
    }

    /**
     * @brief getValue
     * @return
     */
    std::vector<DescSize>& getValue() { return value; }

    /**
     * @brief getKeyPoint
     * @return
     */
    cv::KeyPoint& getKeyPoint() { return keyPoint; }

    /**
     * @brief size
     */
    unsigned size(){ return value.size(); }



    //
    // Printer
    //
    friend std::ostream& operator<<(std::ostream& os, const Descriptor& d)
    {
        if(d.value.size() == 0)
            return os;
        os << d.value.size() << '\n';
        printKeyPoint(os,d.keyPoint);
        os << '\n';
        for(const auto& val : d.value)
            os << (double)val << "   ";
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Descriptor& d)
    {
        unsigned size;
        is >> size;
        d.keyPoint = readKeyPoint(is);
        for(unsigned i = 0; i < size; i++)
        {
            double a;
            is >> a;
            d.value.push_back((DescSize)a);
        }
        return is;
    }



private:
    std::vector<DescSize> value;
    cv::KeyPoint keyPoint;
};



#endif // DESCRIPTOR_H
