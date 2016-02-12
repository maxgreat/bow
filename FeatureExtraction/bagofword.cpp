#include "bagofword.h"

cv::Ptr<cv::xfeatures2d::SIFT> sift = cv::xfeatures2d::SIFT::create(0,1);//Create SIFT detector

std::vector<std::vector<float> > bow::Image2SIFT(cv::Mat& image, int step, bool show)
{
    step = step;
    std::vector<std::vector<float> > dl;
    std::vector<cv::KeyPoint> lkp; //Used to store the detected keypoint
    cv::Mat desc; //Used to store SIFT descriptor
    for(int i = step; i < image.rows-step; i += step){
        for(int j = step; j < image.cols-step; j += step){
            lkp.push_back(cv::KeyPoint(float(j), float(i), float(step*2)));
        }
    }
    sift->compute(image,lkp,desc); //Detect keypoint and Compute sift
    //sift->detectAndCompute(image,cv::noArray(),lkp,desc);
    if(show)
    {
        show = show;
        cv::Mat imageToDraw;
        cv::drawKeypoints(image,lkp,imageToDraw, cv::Scalar::all(-1), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
        cv::imshow("SIFT keypoints",imageToDraw);
    }
    //Store the descriptor (in a cv::Mat) into the vector descList
    for(int i = 0; i < desc.rows; i++){
        std::vector<float> v;
        for(int j = 0; j < desc.cols; j++){
            v.push_back(desc.at<float>(i,j));
        }
        dl.push_back(v);
    }
    return dl;
}


double bow::bowDistance(std::vector<int> &bow1, std::vector<int> &bow2)
{
    if(bow1.size() != bow2.size())
    {
        fprintf(stderr,"EROOR computing distance : vector have to have the same size\n");
        return -1;
    }
    double d = 0;
    for(size_t i = 0; i < bow1.size(); i++)
    {
        d += (bow1[i]-bow2[i])*(bow1[i]-bow2[i]);
    }
    return sqrt(d);
}

float bow::descriptorDistance(std::vector<float>& desc1, std::vector<float>& desc2)
{
    if(desc1.size() != desc2.size())
    {
        fprintf(stderr,"EROOR computing distance : vector have to have the same size\n");
        return -1;
    }
    double d = 0;
    for(size_t i = 0; i < desc1.size(); i++)
    {
        d += (desc1[i]-desc2[i])*(desc1[i]-desc2[i]);
    }
    return sqrt(d);
}





void BagOfWord::AddImage(cv::Mat& image, int step)
{
    if(!clusters.empty())
    {
        fprintf(stderr, "ERROR: BagOfWord : cannot add an image, the cluster are already computed\n");
        return;
    }
    std::vector<std::vector<float> > desc = bow::Image2SIFT(image, step);
    for(auto i : desc)
    {
        descList.push_back(i);
    }
}


void BagOfWord::saveDesc(const std::string& filename, int jump /* = 1 */)
{
    std::ofstream file;
    file.open(filename);
    for(size_t i = 0; i < (descList.size()/jump); i++)
    {
        for(size_t j = 0; j < descList[i*jump].size(); j++)
        {
            file << descList[i*jump][j] << ' ';
        }
        file << std::endl;
    }
    file.close();
}

void BagOfWord::loadCluster(const std::string& filename)
{
    std::ifstream file(filename);
    std::cout << "Read clusters in file " << filename << std::endl << std::flush;
    int i = 0;
    while(!file.eof())
    {
        std::vector<float> vec;
        vec.resize(128);
        for(int i = 0; i < 128; i++)
            file >> vec[i];
        clusters.push_back(vec);
        i++;
    }
    std::cout << "Read " << i << "vector" << std::endl;
    file.close();
}

std::vector<int> BagOfWord::ImageToBOW(cv::Mat& image, bool show)
{
    std::vector<int> vec;
    if(clusters.empty())
    {
        fprintf(stderr, "ERROR: BagOfWord : clusters not computed, cannot compute Bag Of Word\n");
        return vec;
    }
    vec.resize(clusters.size());
    for(size_t i = 0; i < vec.size(); i++) //set vec to 0
        vec[i] = 0;

    std::vector<std::vector<float> > desc = bow::Image2SIFT(image, 8, show);
    cout << "Sift in image :" << desc.size() << endl;
    for(auto& d : desc)
    {
        unsigned int closest = 0;
        double dist = bow::descriptorDistance(clusters[0], d);
        for(size_t i = 1; i < clusters.size(); i++) //looking for the closest cluster
        {
            if(bow::descriptorDistance(clusters[i], d) < dist)
            {
                closest = i;
                dist = bow::descriptorDistance(clusters[i], d);
            }
        }
        vec[closest]++;//+1 in the closest cluster index
    }

    return vec;
}
