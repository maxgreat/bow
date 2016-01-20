#ifndef DESCRIPTOR_C
#define DESCRIPTOR_C

#include "descriptor.h"



std::istream& operator>>(std::istream& is, desc_type& value)
{
    int v;
    is >> v;
    if(v == 1)
        value = desc_type::orb;
    return is;
}

std::ostream& operator<<(std::ostream& os, const desc_type value)
{
    if(value == desc_type::orb)
        os << '1';
    return os;
}






using namespace std;

Descriptor::Descriptor(int size)
{
    value.resize(size);
}

Descriptor::Descriptor(std::vector<double> vd, cv::KeyPoint kp)
{
    if(vd.size() > 0)
    {
        keyPoint = kp;
        value = vd;
    }
}

/*************************************************************
 *
 * Operators
 *
 * ************************************************************/
double& Descriptor::operator[](const unsigned i)
{
    if(i >= value.size())
        throw std::range_error("Out of range");
    else
        return value[i];
}


#endif
