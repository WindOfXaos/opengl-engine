#ifndef LOADER_H
#define LOADER_H

#include <vector>
#include <utility/model.h>

class Loader
{
private:
    std::vector <unsigned int> vaos;
    std::vector <unsigned int> vbos;
    unsigned int createVAO();
    void storeDataInAttributeList(float *data, unsigned int size);
    void unbindVAO();

public:
    Model loadToVAO(float *vertices, unsigned int size);
    void cleanUp();
};

#endif