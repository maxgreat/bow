/**
 * Functions for load and store data used in image2Features
 * @author Maxime Portaz
 */

#ifndef DATASTORAGE_H
#define DATASTORAGE_H

#include <cstdio>
#include <drawing.h>

using namespace std;
using namespace cv;

int loadVectorList(const char * filename, std::vector<std::vector< double> > & listVec){
    FILE* f = fopen(filename, "r");
    int nbVector, vectorSize;

    if(f == NULL){
        fprintf(stderr, "Error openning file");
        return 1;
    }

    fscanf(f, "%d %d", &nbVector, &vectorSize);
    fprintf(stderr, "Reading %d vectors", nbVector);
    listVec.resize(nbVector);
    for(int i = 0; i < nbVector; i++)
    {
        listVec[i].resize(vectorSize);
        for(int j = 0; j < vectorSize; j++){
            fscanf(f, "%lf", &listVec[i][j]);
        }
        loadBar(i, nbVector);
    }
    return 0;
}

int storeVectorList(const char* filename, std::vector<std::vector< double> > listVec){
    FILE* f = fopen(filename, "w");

    if(f == NULL){
        fprintf(stderr, "Error openning file");
        return -1;
    }

    fprintf(f, "%d %d\n", (int)listVec.size(), (int)listVec[0].size());
    for(std::vector<std::vector< double> >::iterator it = listVec.begin(); it != listVec.end();it++){
        for(vector<double>::iterator d = it->begin(); d!= it->end(); d++){
            fprintf(f,"%f ",*d);
        }
        fprintf(f,"\n");
    }


    return 0;

}


std::vector<std::vector< double> > descriptorMat2VectorList(cv::Mat descriptors){
    std::vector<std::vector< double> > descList;
    descList.resize(descriptors.rows);
    for(int i = 0; i < descriptors.rows; i++){
        descList[i].resize(descriptors.cols);
        for(int j = 0; j < descriptors.cols; j++){
            descList[i][j] = descriptors.at<double>(i,j);
        }
    }
    return descList;
}


#endif // DATASTORAGE_H
