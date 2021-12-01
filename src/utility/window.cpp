#include "utility/window.h"

#include <iostream>

Window::Window(const std::string &_title, unsigned int _width, unsigned int _height, bool makeContextCurrent) : title(_title), width(_width), height(_height)
{
  window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
  if (window == NULL)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    exit(-1);
  }

  if (makeContextCurrent)
  {
    glfwMakeContextCurrent(window);
  }
}

Window::~Window()
{
  glfwDestroyWindow(window);
}