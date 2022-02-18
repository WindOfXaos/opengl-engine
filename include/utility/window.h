#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>
#include <string>

// window class
// ------------
class Window
{
private:
    const char *title;
    unsigned int width;
    unsigned int height;

public:
    GLFWwindow *window;
    Window(const char *_title, int _width, int _height);
    ~Window();
};

#endif
