#include "utility/window.h"

#include <iostream>

Window::Window(const char *_title, int _width, int _height)
{
    title = _title;
    width = _width;
    height = _height;

    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(-1);
    }
}

Window::~Window()
{
    glfwDestroyWindow(window);
}