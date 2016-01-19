#include "descriptor.h"

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
