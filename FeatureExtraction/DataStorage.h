/**
 * Functions for load and store data used in image2Features
 * @author Maxime Portaz
 */

#ifndef DATASTORAGE_H
#define DATASTORAGE_H

#include <cstdio>
#include <drawing.h>
#include <vector>

#ifdef USE_OPENCV
#include <opencv2/core/core.hpp>
#include <descriptor.h>
#include "imagedescriptors.h"
#endif

/**
 * @brief loadVectorList
 * @param filename
 * @param listVec
 * @return 0 if load ok, 1 otherwise
 */
int loadVectorList(const std::string filename, std::vector<std::vector<double> > & listVec);

/**
 * @brief storeVectorList
 * @param filename
 * @param listVec
 * @return 0 if storage ok, 1 otherwise
 */
int storeVectorList(const std::string filename, const std::vector<std::vector<double> > & listVec);

/*
#ifdef USE_OPENCV
int storeVectorList(const std::string filename, const std::vector<ImageDescriptors> & listVec);
#endif
*/

/**
 * @brief storeName
 * @param filename
 * @param nameList
 * @return 0 if storage ok, 1 otherwise
 */
int storeName(const std::string filename, const std::vector<std::string> &nameList);

/**
 * @brief loadName
 * @param filename
 * @param nameList
 * @return
 */
int loadName(const std::string filename, std::vector<std::string >& nameList);

#endif // DATASTORAGE_H
