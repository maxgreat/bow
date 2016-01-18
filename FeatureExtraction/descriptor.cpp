#include "descriptor.h"

using namespace std;

Descriptor::Descriptor(int size /* = 128 */)
{
    descriptorSize = size;
    value.resize(descriptorSize);
}

Descriptor::Descriptor(std::vector<double> vd, int size /* = 128 */)
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
