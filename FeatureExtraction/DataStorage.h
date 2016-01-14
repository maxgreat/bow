/**
 * Functions for load and store data used in image2Features
 * @author Maxime Portaz
 */

#ifndef DATASTORAGE_H
#define DATASTORAGE_H

#include <stdio.h>

void loadVectorList(const char * filename, std::vector<std::vector< double> > & listVec){
    FILE* f = fopen(filename, "r");
    int nbVector, vectorSize;

    if(f == NULL){
        fprintf(stderr, "Error openning file");
        return;
    }

    fscanf(f, "%d %d", &nbVector, &vectorSize);
    fprintf(stderr, "Reading %d vectors", nbVector);
    listVec.resize(nbVector);
    int percent = nbVector / 100; //Use to draw the progression
    for(int i = 0; i < nbVector; i++)
    {
        listVec[i].resize(vectorSize);
        for(int j = 0; j < vectorSize; j++){
            fscanf(f, "%lf", &listVec[i][j]);
        }

        /* Draw progression */
        if(i%percent == 0)
            fprintf(stderr, ".");
    }
}



#endif // DATASTORAGE_H
