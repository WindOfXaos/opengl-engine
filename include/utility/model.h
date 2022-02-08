#ifndef MODEL_H
#define MODEL_H

#include <vector>

class Model
{

private:
    unsigned int vaoID;
    unsigned int vertexCount;
    std::vector <unsigned int> textureIDs;

public:
    Model(int vaoID, int vertexCount)
    {
        this->vaoID = vaoID;
        this->vertexCount = vertexCount;
    }

    void addTexture(unsigned int textureID)
    {
        textureIDs.push_back(textureID);
    }

    unsigned int getVaoID()
    {
        return vaoID;
    }

    unsigned int *getTextureIDs()
    {
        return textureIDs.data();
    }

    unsigned int getVertexCount()
    {
        return vertexCount;
    }
};

#endif
