#ifndef RENDERER_H
#define RENDERER_H

#include <utility/model.h>

class Renderer
{
public:
    void prepare();
    void render(Model model);
};

#endif