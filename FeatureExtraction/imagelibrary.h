#ifndef IMAGELIBRARY_H
#define IMAGELIBRARY_H

#include <vector>
#include <glob.h>
#include "imagedescriptors.h"
#include "drawing.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>

template<typename DescType>
class imageLibrary
{
public:
    imageLibrary(desc_type dt) { descriptorType = dt; }

    imageLibrary(desc_type dt, const std::string directory, int nbimage = -1);

    /**
     * @brief selectImages
     * @param directory : directory where the images are
     * @param nb_image : nb images to take
     */
    void addImages(const std::vector<string>& imNameList);

    /**
     * @brief addImage
     * @param im : path to the name to add
     */
    void addImage(const std::string& im);

    friend std::ostream& operator<<(std::ostream& os, const imageLibrary& lib)
    {
        os << lib.imageList.size() << '\n';
        os << lib.descriptorType << '\n';
        for(const auto& im : lib.imageList)
            os << '\t' << im << '\n';
        return os;
    }

    friend std::istream& operator>>(std::istream& is, imageLibrary& lib)
    {
        unsigned size;
        is >> size;
        is >> lib.descriptorType;
        for(unsigned i = 0; i < size; i++)
        {
            ImageDescriptors<DescType> a;
            is >> a;
            lib.imageList.push_back(a);
        }
        return is;
    }

    /* void changeDescType(desc_type t) */

private:
    std::vector<ImageDescriptors<DescType> > imageList;
    desc_type descriptorType;
};

using namespace std;

template<typename T>
imageLibrary<T>::imageLibrary(desc_type dt, const std::string directory, int nbImages /* =-1 */){
    descriptorType = dt;
    //Read the directory for all .jpg
    vector<string> imList;
    glob_t globbuf;
    fprintf(stderr, "GLOB\n");
    glob((directory + "*.jpg").c_str(), GLOB_TILDE, NULL, &globbuf);
    glob((directory + "*.JPG").c_str(), GLOB_TILDE  | GLOB_APPEND, NULL, &globbuf);

    if(globbuf.gl_pathc == 0){
        fprintf(stderr, "No images corresponding to %s\n", directory.c_str());
        return;
    }
    fprintf(stderr, "Add images names from directory\n");
    if(nbImages == -1){
        for(size_t i = 0; i < globbuf.gl_pathc; i++){
            imList.push_back(globbuf.gl_pathv[i]);
            loadBar(i, globbuf.gl_pathc);
        }
    }
    else{
        for(size_t i = 0; i < globbuf.gl_pathc && (int)i < nbImages; i++){
            imList.push_back(globbuf.gl_pathv[i]);
        }
    }

    //Compute descriptor for each image
    addImages(imList);
}


template<typename T>
void imageLibrary<T>::addImages(const std::vector<string>& imNameList)
{
    fprintf(stderr,"Add images to the library\n");
    int i = 0;
    for(const auto &image:imNameList)
    {
        addImage(image);
        loadBar(++i, imNameList.size());
    }
}

template<typename T>
void imageLibrary<T>::addImage(const string& imName)
{
    imageList.push_back(ImageDescriptors<T>(imName, descriptorType));
}





#endif // IMAGELIBRARY_H
