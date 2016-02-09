/**
 * Drawing functions
 * @author Maxime Portaz
 */


#ifndef DRAWING_H
#define DRAWING_H

#include <iomanip>
#include <iostream>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>

using namespace cv;

/**
 * @brief loadBar
 * @param indice
 * @param number
 * @param resolution
 * @param width
 * @author Ross Hemsley
 */
static inline void loadBar(unsigned int x, unsigned int n,unsigned int w = 50)
{
    x++;
    if ( (x != n) && (x % (n/100+1) != 0) ) return;

    float ratio  =  x/(float)n;
    unsigned int   c      =  ratio * w;

    std::cout << std::setw(3) << (int)(ratio*100) << "% [";
    for (unsigned int x=0; x<c; x++) std::cout << "=";
    for (unsigned int x=c; x<w; x++) std::cout << " ";
    if(x != n)
        std::cout << "]\r" << std::flush;
    else
        std::cout << "]\n" << std::flush;
}

/**
 * @brief printKeyPoint
 * @param os
 * @param kp
 */
inline
void printKeyPoint(std::ostream& os, const cv::KeyPoint kp)
{
    os << kp.pt.x << '\n';
    os << kp.pt.y << '\n';
    os << kp.size << '\n';
    os << kp.angle << '\n';
    os << kp.response << '\n';
    os << kp.octave << '\n';
    os << kp.class_id;
}

/**
 * @brief readKeyPoint
 * @param is
 * @return
 */
inline
cv::KeyPoint readKeyPoint(std::istream& is)
{
    cv::Point2f pt;
    float angle, size, response;
    int class_id, octave;
    is >> pt.x >> pt.y;
    is >> size >> angle >> response >> octave >> class_id;
    return cv::KeyPoint(pt,size,angle,response,octave,class_id);
}

#endif // DRAWING_H
