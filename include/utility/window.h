#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>
#include <string>

class Window
{
private:
    GLFWwindow *window;
    const std::string title;
    unsigned int width;
    unsigned int height;

public:
    Window(const std::string &_title, unsigned int _width = 800, unsigned int _height = 600, bool makeContextCurrent = true);
    ~Window();

    unsigned int getWidth() const
    {
        return width;
    }

    unsigned int getHeight() const
    {
        return height;
    }

    const std::string &getTitle() const
    {
        return title;
    }

    GLFWwindow *data() const
    {
        return window;
    }

    bool getWindowShouldClose() const
    {
        return glfwWindowShouldClose(window);
    }

    void swapBuffers()
    {
        glfwSwapBuffers(window);
    }

    // setters
    void setFramebufferSizeCallback(void (*f)(GLFWwindow *, int, int))
    {
        glfwSetFramebufferSizeCallback(window, f);
    }

    void setMouseScrollCallback(void (*f)(GLFWwindow *, double, double))
    {
        glfwSetScrollCallback(window, f);
    }

    void setCursorPosCallback(void (*f)(GLFWwindow *, double, double))
    {
        glfwSetCursorPosCallback(window, f);
    }
};

#endif