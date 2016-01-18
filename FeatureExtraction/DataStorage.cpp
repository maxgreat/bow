/**
 * @author Maxime Portaz
 */
#include "DataStorage.h"

using namespace std;

int loadVectorList(const string filename, std::vector<std::vector<double> > & listVec){
    FILE* f = fopen(filename.c_str(), "r");
    int nbVector, vectorSize;

    if(f == NULL){
        fprintf(stderr, "Error openning file");
        return 1;
    }

    if(fscanf(f, "%d %d", &nbVector, &vectorSize) <= 2)
          return 1;
    fprintf(stderr, "Reading %d vectors", nbVector);
    listVec.resize(nbVector);
    for(int i = 0; i < nbVector; i++)
    {
        listVec[i].resize(vectorSize);
        for(int j = 0; j < vectorSize; j++){
            if(fscanf(f, "%lf", &listVec[i][j]) <= 1)
                return 1;
        }
        loadBar(++i, nbVector);
    }
    return 0;
}

int storeVectorList(const string filename, const std::vector<std::vector< double> > & listVec){
    FILE* f = fopen(filename.c_str(), "w");

    if(f == NULL){
        fprintf(stderr, "Error openning file");
        return 1;
    }
    int i = 0;
    fprintf(f, "%d %d\n", (int)listVec.size(), (int)listVec[0].size());
    for(const auto & it : listVec){
        for(const auto &d : it){
            fprintf(f,"%f ",d);
        }
        fprintf(f,"\n");
        loadBar(++i, listVec.size());
    }


    return 0;

}

#ifdef USE_OPENCV
int storeVectorList(const string filename, const std::vector<ImageDescriptors> & listVec)
{
    FILE* f = fopen(filename.c_str(), "w");

    if(f == NULL)
    {
        fprintf(stderr, "Error openning file");
        return 1;
    }

    fprintf(f, "%d %d\n", (int)listVec.size(), (int)listVec[0].descriptors.size());
    //for (const auto &id : listVec)
    for(size_t i = 0; i < listVec.size(); i++)
    {
        const ImageDescriptors& id = listVec[i];
        for(size_t j = 0; j < id.descriptors.size(); j++)
        {
            const Descriptor& desc = id.descriptors[j];
            for(int k = 0; k < desc.descriptorSize; k++)
            {
                fprintf(f,"%lf",desc.value[k]);
            }
        }
        fprintf(f,"\n");
        loadBar(i, listVec.size());
    }


    return 0;

}
#endif

int storeName(const string filename,const std::vector<string> &nameList){
    FILE* f = fopen(filename.c_str(), "w");

    if(f == NULL){
        fprintf(stderr, "Error openning file");
        return 1;
    }
    fprintf(f, "%d\n", (int)nameList.size());
    for(size_t i = 0; i < nameList.size(); i++)
    {
        fprintf(f,"%s\n",nameList[i].c_str());
        loadBar(i, nameList.size());
    }

    return 0;

}

int loadName(const string filename, std::vector<string> &nameList){
    FILE* f = fopen(filename.c_str(), "r");
    cerr << "Load file " << filename << endl;
    if(f == NULL){
        fprintf(stderr, "Error openning file");
        return 1;
    }
    int size;
    char name[1024];
    if(fscanf(f, "%d\n", &size) < 1)
        return 1;
    for(unsigned int i = 0; i < size; i++)
    {
        if(fscanf(f, "%s", name) < 1)
            return 1;
        nameList.push_back(string(name));
        loadBar(i, size);
    }

    return 0;

}

