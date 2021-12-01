#include <utility/loader.h>

#include <vector>
#include <glad/glad.h>
#include <utility/model.h>

unsigned int Loader::createVAO()
{
    unsigned int vaoID;
    glGenVertexArrays(1, &vaoID);
    vaos.push_back(vaoID);
    glBindVertexArray(vaoID);
    return vaoID;
}

void Loader::storeDataInAttributeList(float *data, unsigned int size)
{
    unsigned int vboID;
    glGenBuffers(1, &vboID);
    vbos.push_back(vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::unbindVAO()
{
    glBindVertexArray(0);
}

Model Loader::loadToVAO(float *vertices, unsigned int size)
{
    unsigned int vaoID = createVAO();
    storeDataInAttributeList(vertices, size * sizeof(vertices));
    unbindVAO();
    return Model(vaoID, size / 8);
}

void Loader::cleanUp()
{
    for (auto vao : vaos)
    {
        glDeleteVertexArrays(1, &vao);
    }
    for (auto vbo : vbos)
    {
        glDeleteBuffers(1, &vbo);
    }
}