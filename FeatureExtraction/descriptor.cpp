#ifndef DESCRIPTOR_C
#define DESCRIPTOR_C

#include "descriptor.h"


std::istream& operator>>(std::istream& is, desc_type& value)
{
    int v;
    is >> v;
    if(v == 1)
        value = desc_type::orb;
    else if(v == 2)
        value = desc_type::akaze;
    return is;
}

std::ostream& operator<<(std::ostream& os, const desc_type value)
{
    if(value == desc_type::orb)
        os << '1';
    else if(value == desc_type::akaze)
        os << '2';
    return os;
}

#endif
