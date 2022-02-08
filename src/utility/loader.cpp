#include <utility/loader.h>

#include <vector>
#include <glad/glad.h>
#include <utility/model.h>
#include <utility/texture.h>

unsigned int Loader::createVAO()
{
    unsigned int vaoID;
    glGenVertexArrays(1, &vaoID);
    vaos.push_back(vaoID);
    glBindVertexArray(vaoID);
    return vaoID;
}

void Loader::storeDataInAttributeList(unsigned int attribNum, unsigned int coordSize, float *data, unsigned int size)
{
    unsigned int vboID;
    glGenBuffers(1, &vboID);
    vbos.push_back(vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    glVertexAttribPointer(attribNum, coordSize, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(attribNum);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::unbindVAO()
{
    glBindVertexArray(0);
}

Model Loader::loadToVAO(
        float *positions, float *normals, float *texCoords,
        unsigned int sizeP, unsigned int sizeN, unsigned int sizeT)
{
    unsigned int vaoID = createVAO();
    storeDataInAttributeList(0, 3, positions, sizeP * sizeof(positions));
    storeDataInAttributeList(1, 3, normals, sizeN * sizeof(normals));
    storeDataInAttributeList(2, 2, texCoords, sizeT * sizeof(texCoords));
    unbindVAO();
    return Model(vaoID, sizeP / 3);
}

unsigned int Loader::loadTexture(int enumType, const char *file, int rgbType, bool flip)
{
    Texture texture;    
    texture.bind(enumType);
    texture.generateTexture(file, rgbType, flip);
    unsigned int textureID = texture.getTextureID();
    textures.push_back(textureID);
    return textureID;
}

void Loader::cleanUp()
{
    // clean VAOS
    for (auto vao : vaos)
    {
        glDeleteVertexArrays(1, &vao);
    }
    // clean VBOS
    for (auto vbo : vbos)
    {
        glDeleteBuffers(1, &vbo);
    }
    // clean textures
    for (auto texture : textures)
    {
        glDeleteTextures(1, &texture);
    }
}
