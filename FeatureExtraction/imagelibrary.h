#ifndef IMAGELIBRARY_H
#define IMAGELIBRARY_H

#include <vector>
#include <glob.h>
#include "imagedescriptors.h"
#include "descriptor.h"
#include "drawing.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>

enum desc_type {orb}; /* TODO : add other descriptors */


class imageLibrary
{
public:
    imageLibrary();

    /**
     * @brief selectImages
     * @param directory : directory where the images are
     * @param nb_image : nb images to take
     * @return list of images
     */
    void addImages(const std::string directory, int nbImages=-1);

    void addImages(const std::vector<string>& imNameList);

    void addImage(ImageDescriptors& im);

    void addImage(const std::string& im);

    friend std::ostream& operator<<(std::ostream& os, const imageLibrary& lib)
    {
        os << lib.imageList.size() << '\n';
        os << lib.descriptorType << '\n';
        for(const auto& im : imageList)
            os << im << '\n';
        return os;
    }

    friend std::istream& operator<<(std::istream& is, imageLibrary& lib)
    {
        unsigned size;
        is >> size;
        is >> lib.descriptorType;
        for(unsigned i = 0; i < size; i++)
        {
            ImageDescriptors a;
            is >> a;
            imageList.push_back(a);
        }
        return is;
    }

    /* void changeDescType(desc_type t) */

private:
    std::vector<ImageDescriptors> imageList;
    desc_type descriptorType;
};

#endif // IMAGELIBRARY_H
