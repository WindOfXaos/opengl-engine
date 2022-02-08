#ifndef LOADER_H
#define LOADER_H

#include <vector>
#include <utility/model.h>

class Loader
{
private:
    std::vector <unsigned int> vaos;
    std::vector <unsigned int> vbos;
    std::vector <unsigned int> textures;

    unsigned int createVAO();
    void storeDataInAttributeList(unsigned int attribNum, unsigned int coordSize, float *data, unsigned int size);
    void unbindVAO();

public:
    Model loadToVAO(
        float *positions, float *normals, float *textures,
        unsigned int sizeP, unsigned int sizeN, unsigned int sizeT);
    unsigned int loadTexture(int enumType, const char *file, int rgbType, bool flip = false);
    void cleanUp();
};

#endif
