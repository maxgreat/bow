#include "descriptor.h"

using namespace std;

Descriptor::Descriptor(int size)
{
    descriptorSize = size;
    value.resize(descriptorSize);
}



Descriptor::Descriptor(std::vector<double> vd)
{
    descriptorSize = vd.size();
    value = vd;
}


Descriptor::Descriptor(std::vector<double> vd, int size)
{
    descriptorSize = size;
    if(vd.size() == size){
        value = vd;
    }
    else{
        fprintf(stderr, "Error vector size\n");
        value.resize(descriptorSize);
    }
}
