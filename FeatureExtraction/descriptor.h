/**
 * Handle image descriptor generated with openCV
 * @author Maxime Portaz
 */

#ifndef DESCRIPTOR_H
#define DESCRIPTOR_H

#include <cstdio>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>

/**
 * Class Descriptor
 */
class Descriptor
{
public:
    Descriptor(int size = 128);

    Descriptor(std::vector<double> vd, int size = 128);

    int descriptorSize;
    std::vector<double> value;
};

#endif // DESCRIPTOR_H
