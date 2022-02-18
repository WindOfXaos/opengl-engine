#include <utility/renderer.h>
#include <glad/glad.h>
#include <utility/model.h>

void Renderer::prepare(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::render(Model model) {
    glBindVertexArray(model.getVaoID());

    // textures binding (diffuse and specular)
    unsigned int *textureIDs = model.getTextureIDs();
    unsigned int IDs = model.getNumOfTextIDs();
    for(unsigned int i = 0; i < IDs; i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, textureIDs[i]);
    }

    glDrawArrays(GL_TRIANGLES, 0, model.getVertexCount());
    glBindVertexArray(0);
}
