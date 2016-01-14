/**
 * Functions for load and store data used in image2Features
 * @author Maxime Portaz
 */

#ifndef DATASTORAGE_H
#define DATASTORAGE_H

#include <cstdio>
#include <drawing.h>
#include <vector>

/**
 * @brief loadVectorList
 * @param filename
 * @param listVec
 * @return 0 if load ok, 1 otherwise
 */
int loadVectorList(const char * filename, std::vector<std::vector<double> > & listVec);

/**
 * @brief storeVectorList
 * @param filename
 * @param listVec
 * @return 0 if storage ok, 1 otherwise
 */
int storeVectorList(const char* filename, std::vector<std::vector< double> > listVec);


#endif // DATASTORAGE_H
