#include <utility/renderer.h>
#include <glad/glad.h>
#include <utility/model.h>

void Renderer::prepare() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::render(Model model) {
    glBindVertexArray(model.getVaoID());

    // textures binding (diffuse and specular)
    unsigned int *textureIDs = model.getTextureIDs();
    // note: number of iterations or textures is hardcoded 
    // to (diff&spec textures) i = 2; temporary solution
    // TODO: use C++ libraries instead of normal arrays
    for(unsigned int i = 0; i < 2; i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, textureIDs[i]);
    }

    glDrawArrays(GL_TRIANGLES, 0, model.getVertexCount());
    glBindVertexArray(0);
}
