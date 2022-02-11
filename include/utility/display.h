#ifndef DISPLAY_H
#define DISPLAY_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <utility/camera.h>
#include <utility/window.h>

namespace Display
{
    // namespace variables
    // -------------------
    extern const unsigned int SCR_WIDTH;
    extern const unsigned int SCR_HEIGHT;
    extern const char *SCR_TITLE;
    extern Camera camera;
    extern Window *mainWindow;

    extern float lastX;
    extern float lastY;
    extern bool firstMouse;
    extern float deltaTime;
    extern float lastFrame;

    // namespace functions
    // -------------------
    void Initialize();
    void Clear(float r, float g, float b, float a);
    void Update();
    bool Closed();
    void Terminate();

    // callback functions
    // ------------------
    void framebuffer_size_callback(GLFWwindow *window, int width, int height);
    void mouse_callback(GLFWwindow *window, double xpos, double ypos);
    void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
    void processInput(GLFWwindow *window);
};
#endif
