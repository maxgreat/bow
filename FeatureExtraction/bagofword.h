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
    std::vector<std::vector<float> > Image2SIFT(cv::Mat& image);

    float bowDistance(std::vector<int> bow1, std::vector<int> bow2);

    float descriptorDistance(std::vector<float> bow1, std::vector<float> bow2);
}



class BagOfWord
{
public:
    BagOfWord() { }

    void AddImage(cv::Mat& image);

    void AddImage(const std::string& imName)
    {
        cv::Mat image = cv::imread(imName);
        AddImage(image);
    }

    void saveDesc(const std::string& filename, int jump = 1);

    void loadCluster(const std::string& filename);

    std::vector<int> ImageToBOW(cv::Mat& image);

    bool isInit = false;

private:
    std::vector<std::vector<float> > clusters;
    std::vector<std::vector<float> > descList;
};

#endif // BAGOFWORD_H
