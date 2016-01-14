/**
 * Drawing functions
 * @author Maxime Portaz
 */


#ifndef DRAWING_H
#define DRAWING_H

#include <iomanip>
#include <iostream>
#include <vector>

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
    if ( (x != n) && (x % (n/100+1) != 0) ) return;

    float ratio  =  x/(float)n;
    unsigned int   c      =  ratio * w;

    std::cout << std::setw(3) << (int)(ratio*100) << "% [";
    for (unsigned int x=0; x<c; x++) std::cout << "=";
    for (unsigned int x=c; x<w; x++) std::cout << " ";
    std::cout << "]\r" << std::flush;
}


#endif // DRAWING_H
