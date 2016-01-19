#include "imagedescriptors.h"


void ImageDescriptors::addDescriptor(Descriptor d)
{
    descriptors.push_back(d);
}

void ImageDescriptors::addDescriptor(std::vector<Descriptor>& descList)
{
    for(auto &desc : descList)
            descriptors.push_back(desc);
}
