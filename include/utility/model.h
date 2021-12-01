#ifndef MODEL_H
#define MODEL_H

class Model
{

private:
    unsigned int vaoID;
    unsigned int vertexCount;

public:
    Model(int vaoID, int vertexCount)
    {
        this->vaoID = vaoID;
        this->vertexCount = vertexCount;
    }

    unsigned int getVaoID()
    {
        return vaoID;
    }

    unsigned int getVertexCount()
    {
        return vertexCount;
    }
};

#endif