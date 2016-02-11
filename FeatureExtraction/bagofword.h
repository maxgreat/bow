#ifndef BAGOFWORD_H
#define BAGOFWORD_H

#include <cstdio>
#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>

namespace bow
{
    std::vector<std::vector<float> > Image2SIFT(cv::Mat& image, int step = 8, bool show = false);

    float bowDistance(std::vector<int> bow1, std::vector<int> bow2);

    float descriptorDistance(std::vector<float> bow1, std::vector<float> bow2);
}



class BagOfWord
{
public:
    BagOfWord() { }

    void AddImage(cv::Mat& image, int step = 16);

    void AddImage(const std::string& imName, int step = 16)
    {
        cv::Mat image = cv::imread(imName);
        AddImage(image, step);
    }

    void saveDesc(const std::string& filename, int jump = 1);

    void loadCluster(const std::string& filename);

    std::vector<int> ImageToBOW(cv::Mat& image, bool show = false);

    bool isInit = false;

    std::vector<std::vector<float> >& getClusters()
    {
        return clusters;
    }

private:
    std::vector<std::vector<float> > clusters;
    std::vector<std::vector<float> > descList;
};

#endif // BAGOFWORD_H
