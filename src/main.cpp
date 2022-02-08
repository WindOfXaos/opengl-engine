#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <utility/shader.h>
#include <utility/loader.h>
#include <utility/model.h>
#include <utility/renderer.h>
#include <utility/display.h>

#include <iostream>

#define GET_VARIABLE_NAME(var) (#var)
#define GET_ARRAY_SIZE(arr) (*(&arr + 1) - arr)


// lighting
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

struct DirLight 
{
    glm::vec3 direction = glm::vec3(-0.2f, -1.0f, -0.3f);
    glm::vec3 ambient = glm::vec3(0.05f, 0.05f, 0.05f);
    glm::vec3 diffuse = glm::vec3(0.4f, 0.4f, 0.4f);
    glm::vec3 specular = glm::vec3(0.5f, 0.5f, 0.5f);
} sun;  

struct PointLight 
{   
    glm::vec3 position = glm::vec3(0.0f);
    glm::vec3 ambient = glm::vec3(0.05f, 0.05f, 0.05f);
    glm::vec3 diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
    glm::vec3 specular = glm::vec3(1.0f, 1.0f, 1.0f);

    float constant = 1.0f;
    float linear = 0.09;
    float quadratic = 0.032;  
} redstoneLight;

// set up vertex data (and buffer(s)) and configure vertex attributes
// ------------------------------------------------------------------
float positions[] = {
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
                       
    -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,
                       
    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
                       
    0.5f,  0.5f,  0.5f,
    0.5f,  0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f, -0.5f,  0.5f,
    0.5f,  0.5f,  0.5f,
                       
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f, -0.5f,
                       
    -0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f
};

float normals[] = {
     0.0f,  0.0f, -1.0f,
     0.0f,  0.0f, -1.0f, 
     0.0f,  0.0f, -1.0f, 
     0.0f,  0.0f, -1.0f, 
     0.0f,  0.0f, -1.0f,
     0.0f,  0.0f, -1.0f,
                        
     0.0f,  0.0f,  1.0f,
     0.0f,  0.0f,  1.0f, 
     0.0f,  0.0f,  1.0f, 
     0.0f,  0.0f,  1.0f, 
     0.0f,  0.0f,  1.0f,
     0.0f,  0.0f,  1.0f,
                        
    -1.0f,  0.0f,  0.0f,
    -1.0f,  0.0f,  0.0f,
    -1.0f,  0.0f,  0.0f,
    -1.0f,  0.0f,  0.0f,
    -1.0f,  0.0f,  0.0f,
    -1.0f,  0.0f,  0.0f,
                        
     1.0f,  0.0f,  0.0f, 
     1.0f,  0.0f,  0.0f, 
     1.0f,  0.0f,  0.0f, 
     1.0f,  0.0f,  0.0f, 
     1.0f,  0.0f,  0.0f, 
     1.0f,  0.0f,  0.0f, 
                        
     0.0f, -1.0f,  0.0f,
     0.0f, -1.0f,  0.0f, 
     0.0f, -1.0f,  0.0f, 
     0.0f, -1.0f,  0.0f, 
     0.0f, -1.0f,  0.0f,
     0.0f, -1.0f,  0.0f,
                        
     0.0f,  1.0f,  0.0f,
     0.0f,  1.0f,  0.0f, 
     0.0f,  1.0f,  0.0f, 
     0.0f,  1.0f,  0.0f, 
     0.0f,  1.0f,  0.0f,
     0.0f,  1.0f,  0.0f
};

float texCoords[] = {
     0.0f,  0.0f,
     1.0f,  0.0f,
     1.0f,  1.0f,
     1.0f,  1.0f,
     0.0f,  1.0f,
     0.0f,  0.0f,
                 
     0.0f,  0.0f,
     1.0f,  0.0f,
     1.0f,  1.0f,
     1.0f,  1.0f,
     0.0f,  1.0f,
     0.0f,  0.0f,
                 
     1.0f,  0.0f,
     1.0f,  1.0f,
     0.0f,  1.0f,
     0.0f,  1.0f,
     0.0f,  0.0f,
     1.0f,  0.0f,
                 
     1.0f,  0.0f,
     1.0f,  1.0f,
     0.0f,  1.0f,
     0.0f,  1.0f,
     0.0f,  0.0f,
     1.0f,  0.0f,
                 
     0.0f,  1.0f,
     1.0f,  1.0f,
     1.0f,  0.0f,
     1.0f,  0.0f,
     0.0f,  0.0f,
     0.0f,  1.0f,
                 
     0.0f,  1.0f,
     1.0f,  1.0f,
     1.0f,  0.0f,
     1.0f,  0.0f,
     0.0f,  0.0f,
     0.0f,  1.0f
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
    Display::Initialize();
    
    // initialize loader and renderer
    // ------------------------------
    Loader loader;
    Renderer renderer;

    // build and compile shaders
    // -------------------------
    Shader redstoneShader("shaders/redstonelamp.vs", "shaders/redstonelamp.fs");

    // load vertices and textures
    // -------------
    Model redstone = loader.loadToVAO(positions, normals, texCoords,
    GET_ARRAY_SIZE(positions), GET_ARRAY_SIZE(normals), GET_ARRAY_SIZE(texCoords));

    const char *diffuseMap = "assets/textures/redstone_lamp.jpg";   
    redstone.addTexture(loader.loadTexture(GL_TEXTURE_2D, diffuseMap, GL_RGB));

    const char *specularMap = "assets/textures/redstone_lamp_specular.png";   
    redstone.addTexture(loader.loadTexture(GL_TEXTURE_2D, specularMap, GL_RGBA, true));

    // shader configuration
    // --------------------
    redstoneShader.use();
    redstoneShader.setInt("material.diffuse", 0);
    redstoneShader.setInt("material.specular", 1);


    // render loop
    // -----------
    while (!Display::Closed())
    {
        Display::Update();
        Display::Clear(0.1f, 0.1f, 0.1f, 1.0f);

        // render
        // ------
        renderer.prepare();

        //TODO: encapsulate lighting code in a class maybe
        redstoneShader.use();
        redstoneShader.setVec3("viewPos", Display::camera.position);
        redstoneShader.setFloat("material.shininess", 32.0f);

        // directional light
        redstoneShader.setVec3("dirLight.direction", sun.direction);
        redstoneShader.setVec3("dirLight.ambient", sun.ambient);
        redstoneShader.setVec3("dirLight.diffuse", sun.diffuse);
        redstoneShader.setVec3("dirLight.specular", sun.specular);

        // point lights
        unsigned int nmPointLights = GET_ARRAY_SIZE(pointLightPositions);
        for (unsigned int i = 0; i < nmPointLights; i++)
        {
            std::string pointLight = "pointLights[" + std::to_string(i) + "].";
            redstoneShader.setVec3(pointLight + "position", pointLightPositions[i]);
            redstoneShader.setVec3(pointLight + "ambient", redstoneLight.ambient);
            redstoneShader.setVec3(pointLight + "diffuse", redstoneLight.diffuse);
            redstoneShader.setVec3(pointLight + "specular", redstoneLight.specular);
            redstoneShader.setFloat(pointLight + "constant", redstoneLight.constant);
            redstoneShader.setFloat(pointLight + "linear", redstoneLight.linear);
            redstoneShader.setFloat(pointLight + "quadratic", redstoneLight.quadratic); 
            redstoneShader.setInt("nmPointLights", nmPointLights);
        } 

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(Display::camera.zoom),
                (float)Display::SCR_WIDTH / (float)Display::SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = Display::camera.GetViewMatrix();
        redstoneShader.setMat4("projection", projection);
        redstoneShader.setMat4("view", view);

        // world transformation
        glm::mat4 model = glm::mat4(1.0f);
        redstoneShader.setMat4("model", model);

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

    }

    // de-allocate all resources
    // -------------------------
    loader.cleanUp();
    Display::Terminate();
    
    return 0;
}
