#ifndef RENDERER_H
#define RENDERER_H

#include <utility/model.h>

class Renderer
{
public:
    void prepare(float r, float g, float b, float a);
    void render(Model model);
};

#endif
