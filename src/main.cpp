#include"imgui.h"
#include"imgui_impl_glfw.h"
#include"imgui_impl_opengl3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <utility/shader.h>
#include <utility/loader.h>
#include <utility/model.h>
#include <utility/renderer.h>
#include <utility/display.h>
#include <utility/light.h>

#include <iostream>

#define GET_VARIABLE_NAME(var) (#var)
#define GET_ARRAY_SIZE(arr) (*(&arr + 1) - arr)

void imguiInit(GLFWwindow *window);
void imguiPrepare();
void imguiUpdate();
void imguiTerminate();

glm::vec4 skyColor(0.1f, 0.1f, 0.1f, 1.0f);

Material mat{
    32.0f,  // shininess
    1.0f    // reflectivity
};

DirLight sun{
    glm::vec3(-0.2f, -1.0f, -0.3f), // direction
    glm::vec3(0.05f, 0.05f, 0.05f), // ambient
    glm::vec3(0.4f, 0.4f, 0.4f),    // diffuse
    glm::vec3(0.5f, 0.5f, 0.5f)     // specular 
};

PointLight redstoneLights{
    4,                  // length
    (glm::vec3 []){     // positions
        glm::vec3( 0.7f,  0.2f,  2.0f),
        glm::vec3( 2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3( 0.0f,  0.0f, -3.0f)
    },

    glm::vec3(0.05f, 0.05f, 0.05f),  // ambient
    glm::vec3(0.8f, 0.8f, 0.8f),     // diffuse
    glm::vec3(1.0f, 1.0f, 1.0f),     // specular

    1.0f,  // constant
    0.09, // linear
    0.032 // quadratic
};

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

int main()
{
    // initialize glfw ,glad and ImGui
    // -------------------------------
    Display::Initialize();
    imguiInit(Display::mainWindow->window);

    // initialize loader and renderer
    // ------------------------------
    Loader loader;
    Renderer renderer;

    // build and compile shaders
    // -------------------------
    Shader redstoneShader("shaders/redstonelamp.vs", "shaders/redstonelamp.fs");

    // load vertices and textures
    // --------------------------
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
        // declare new imgui frame
        imguiPrepare();

        // render
        // ------
        renderer.prepare(skyColor.r, skyColor.g, skyColor.b, skyColor.a);

        // light shaders
        // -------------
        redstoneShader.use();
        redstoneShader.setVec3("viewPos", Display::camera.position);
        redstoneShader.setMaterial(mat.shininess, mat.reflectivity);

        // directional light
        redstoneShader.setDirLight(sun);

        // point lights
        redstoneShader.setPointLight(redstoneLights);

        // view/projection transformations
        // -------------------------------
        glm::mat4 projection = glm::perspective(glm::radians(Display::camera.zoom),
                (float)Display::SCR_WIDTH / (float)Display::SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = Display::camera.GetViewMatrix();
        redstoneShader.setMat4("projection", projection);
        redstoneShader.setMat4("view", view);

        // world transformation
        // --------------------
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

        // imgui UI contents
        // -----------------
        ImGui::Begin("Settings");
        ImGui::ColorEdit4("Sky Color", (float*)&skyColor);
        ImGui::Separator();
        if (ImGui::TreeNode("Lighting Configuration"))
        {
            ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
            if (ImGui::BeginTabBar("Lighting Configuration", tab_bar_flags))
            {
                if (ImGui::BeginTabItem("Sun"))
                {
                    ImGui::SliderFloat3("Direction", (float*)&sun.direction, 100.0f, -100.0f);
                    ImGui::ColorEdit3("Ambient", (float*)&sun.ambient);
                    ImGui::ColorEdit3("Diffuse", (float*)&sun.diffuse);
                    ImGui::ColorEdit3("Specular", (float*)&sun.specular);             
                    ImGui::EndTabItem();
                }
                if (ImGui::BeginTabItem("Redstone Lamp"))
                {
                    ImGui::ColorEdit3("Ambient", (float*)&redstoneLights.ambient);
                    ImGui::ColorEdit3("Diffuse", (float*)&redstoneLights.diffuse);
                    ImGui::ColorEdit3("Specular", (float*)&redstoneLights.specular);             

                    // plot attenuation formula in real-time
                    ImGui::Separator();
                    ImGui::Text("Distance Parameters");
                    struct Funcs{
                        static float Atten(void*, int i) {return 1.0/(1.0 + redstoneLights.linear*i + redstoneLights.quadratic*i*i);}
                    };
                    float (*func)(void*, int) = Funcs::Atten;
                    ImGui::PlotLines("", func, NULL, 20, 0, "Intensity VS. Distance", 0.0f, 1.2f, ImVec2(0, 80));
                    ImGui::SliderFloat2("", (float*) &redstoneLights.linear, 0.0f, 4.0f);
                    ImGui::EndTabItem();
                }
                ImGui::EndTabBar();
            }
            ImGui::TreePop();
        }
        if (ImGui::TreeNode("Materials Configuration"))
        {
            ImGui::SliderFloat("Shininess", &mat.shininess, 1.0f, 256.0f);
            ImGui::SliderFloat("Reflectivity", &mat.reflectivity, 0.0f, 1.0f);
            ImGui::TreePop();
        }
        ImGui::End();

        // update ImGui and display
        imguiUpdate();
        Display::Update();
    }

    // de-allocate all resources
    // -------------------------
    loader.cleanUp();
    Display::Terminate();
    imguiTerminate();

    return 0;
}

void imguiInit(GLFWwindow *window)
{
    IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

void imguiPrepare()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void imguiUpdate()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void imguiTerminate()
{
    ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}
