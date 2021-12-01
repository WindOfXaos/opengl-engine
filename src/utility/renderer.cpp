#include <utility/renderer.h>
#include <glad/glad.h>
#include <utility/model.h>

void Renderer::prepare() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::render(Model model) {
    glBindVertexArray(model.getVaoID());
    glDrawArrays(GL_TRIANGLES, 0, model.getVertexCount());
    glBindVertexArray(0);
}
