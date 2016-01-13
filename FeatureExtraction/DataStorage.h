#ifndef DATASTORAGE_H
#define DATASTORAGE_H

#include <stdio.h>

void loadVectorList(const char * filename, std::vector<std::vector< double> > & listVec){
    FILE* f = fopen(filename, "r");
    int nbVector, vectorSize;

    if(f == NULL){
        fprintf(stderr, "Error openning file");
        return;
    } else {
        fprintf(stderr, "open file ok.");
    }

    fscanf(f, "%d %d", &nbVector, &vectorSize);
    fprintf(stderr, "Nb Vector : %d \nVector Size : %d\n", nbVector, vectorSize);
    listVec.resize(nbVector);
    for(int i = 0; i < nbVector; i++)
    {
        fprintf(stderr, "On commence les choses serieuses\ni = %d\n", i);
        listVec[i].resize(vectorSize);
        fprintf(stderr, "On a resize le bidul\n");
        for(int j = 0; j < vectorSize; i++){
            printf("On essaie maintenant de scanf\n");
            fscanf(f, "%lf", &listVec[i][j]);
            printf("Vector %d %d = %f", i, j, listVec[i][j]);
        }
    }
}



#endif // DATASTORAGE_H
