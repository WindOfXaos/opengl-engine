#include "utility/display.h"

namespace Display{
    // namespace variables
    // -------------------
    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;
    const char *SCR_TITLE = "OpenGL";
    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
    Window *mainWindow;

    float lastX = SCR_WIDTH / 2.0f;
    float lastY = SCR_HEIGHT / 2.0f;
    bool firstMouse = true;
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
}

void Display::Initialize()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    mainWindow = new Window(SCR_TITLE, SCR_WIDTH, SCR_HEIGHT);
    glfwMakeContextCurrent(mainWindow->window);
    glfwSetFramebufferSizeCallback(mainWindow->window, framebuffer_size_callback);
    glfwSetCursorPosCallback(mainWindow->window, mouse_callback);
    glfwSetScrollCallback(mainWindow->window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(mainWindow->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(-1);
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
}

void Display::Terminate()
{
    delete mainWindow;
    glfwTerminate();
}

void Display::Clear(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Display::Update()
{
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    processInput(mainWindow->window);
    glfwSwapBuffers(mainWindow->window);
    glfwPollEvents();
}
bool Display::Closed()
{
    return glfwWindowShouldClose(mainWindow->window);
}

void Display::processInput(GLFWwindow *window)
{
    // close window on ESC key
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // movement usig WASD keys
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);

    // unlock mouse while ALT key is pressed
    // TODO: stop imgui from handling mouse events
    if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
    {
        firstMouse = true;
        glfwSetCursorPosCallback(mainWindow->window, NULL);
        glfwSetInputMode(mainWindow->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    else
    {
        glfwSetCursorPosCallback(mainWindow->window, mouse_callback);
        glfwSetInputMode(mainWindow->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
}

// window resize callback function
// -------------------------------
void Display::framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// mouse movement callback function
// --------------------------------
void Display::mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// mouse scroll wheel callback function
// ------------------------------------
void Display::scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}
