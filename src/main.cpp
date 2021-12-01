#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <utility/shader.h>
#include <utility/camera.h>
#include <utility/window.h>
#include <utility/texture.h>
#include <utility/utility.h>
#include <utility/loader.h>
#include <utility/model.h>
#include <utility/renderer.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// lighting
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

// set up vertex data (and buffer(s)) and configure vertex attributes
// ------------------------------------------------------------------
float vertices[] = {
    // positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
    0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
    0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
    0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
    0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

    0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
    0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
    0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
    0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
    0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
    0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
    0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
    0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};
// positions all containers
glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f),
    glm::vec3( 2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3( 2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3( 1.3f, -2.0f, -2.5f),
    glm::vec3( 1.5f,  2.0f, -2.5f),
    glm::vec3( 1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
};
// positions of the point lights
glm::vec3 pointLightPositions[] = {
    glm::vec3( 0.7f,  0.2f,  2.0f),
    glm::vec3( 2.3f, -3.3f, -4.0f),
    glm::vec3(-4.0f,  2.0f, -12.0f),
    glm::vec3( 0.0f,  0.0f, -3.0f)
};
int main()
{
    // glfw: initialize and configure
    // ------------------------------
    Utility::initalizeGLFW();

    // glfw window creation
    // --------------------
    Window window("Opengl", SCR_WIDTH, SCR_HEIGHT);
    window.setFramebufferSizeCallback(framebuffer_size_callback);
    window.setMouseScrollCallback(scroll_callback);
    window.setCursorPosCallback(mouse_callback);

    // tell GLFW to capture mouse
    glfwSetInputMode(window.data(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    Utility::initializeGLAD();

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // initialize loader and renderer
    // ------------------------------
    Loader loader;
    Renderer renderer;

    // build and compile shader
    // ------------------------
    Shader redstoneShader("shaders/redstonelamp.vs", "shaders/redstonelamp.fs");

    // load vertices
    // -------------
    Model redstone = loader.loadToVAO(vertices, sizeof(vertices)/sizeof(vertices[0]));

    // load textures
    // -------------
    Texture diffuseMap;
    Texture specularMap;
    diffuseMap.bind(GL_TEXTURE_2D);
    diffuseMap.generateTexture("assets/textures/redstone_lamp.jpg", GL_RGB);
    specularMap.bind(GL_TEXTURE_2D);
    specularMap.generateTexture("assets/textures/redstone_lamp_specular.png", GL_RGBA, true);

    // shader configuration
    // --------------------
    redstoneShader.use();
    redstoneShader.setInt("material.diffuse", 0);
    redstoneShader.setInt("material.specular", 1);


    // render loop
    // -----------
    while (!window.getWindowShouldClose())
    {
        // per-frame time logic
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window.data());
        window.swapBuffers();

        // render
        // ------
        renderer.prepare();

        //TODO: encapsulate lighting code in a class maybe
        redstoneShader.use();
        redstoneShader.setVec3("viewPos", camera.position);
        redstoneShader.setFloat("material.shininess", 32.0f);

        // directional light
        redstoneShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
        redstoneShader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
        redstoneShader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
        redstoneShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
        // point light 1
        redstoneShader.setVec3("pointLights[0].position", pointLightPositions[0]);
        redstoneShader.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
        redstoneShader.setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
        redstoneShader.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
        redstoneShader.setFloat("pointLights[0].constant", 1.0f);
        redstoneShader.setFloat("pointLights[0].linear", 0.09);
        redstoneShader.setFloat("pointLights[0].quadratic", 0.032);
        // point light 2
        redstoneShader.setVec3("pointLights[1].position", pointLightPositions[1]);
        redstoneShader.setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
        redstoneShader.setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
        redstoneShader.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
        redstoneShader.setFloat("pointLights[1].constant", 1.0f);
        redstoneShader.setFloat("pointLights[1].linear", 0.09);
        redstoneShader.setFloat("pointLights[1].quadratic", 0.032);
        // point light 3
        redstoneShader.setVec3("pointLights[2].position", pointLightPositions[2]);
        redstoneShader.setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
        redstoneShader.setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
        redstoneShader.setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
        redstoneShader.setFloat("pointLights[2].constant", 1.0f);
        redstoneShader.setFloat("pointLights[2].linear", 0.09);
        redstoneShader.setFloat("pointLights[2].quadratic", 0.032);
        // point light 4
        redstoneShader.setVec3("pointLights[3].position", pointLightPositions[3]);
        redstoneShader.setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
        redstoneShader.setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
        redstoneShader.setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
        redstoneShader.setFloat("pointLights[3].constant", 1.0f);
        redstoneShader.setFloat("pointLights[3].linear", 0.09);
        redstoneShader.setFloat("pointLights[3].quadratic", 0.032);    

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera.zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        redstoneShader.setMat4("projection", projection);
        redstoneShader.setMat4("view", view);

        // world transformation
        glm::mat4 model = glm::mat4(1.0f);
        redstoneShader.setMat4("model", model);

        // bind diffuse map
        glActiveTexture(GL_TEXTURE0);
        diffuseMap.bind(GL_TEXTURE_2D);
        // bind specular map
        glActiveTexture(GL_TEXTURE1);
        specularMap.bind(GL_TEXTURE_2D);
        
        // render containers
        for (unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            redstoneShader.setMat4("model", model);
            renderer.render(redstone);
        }

        //TODO: add Imgui function

        glfwPollEvents();
    }

    // de-allocate all resources
    // -------------------------
    loader.cleanUp();
    glfwTerminate();
    
    return 0;
}

// process all input
// -----------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

//TODO: add mouse release function

// window resize callback function
// -------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// mouse movement callback function
// --------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
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
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}