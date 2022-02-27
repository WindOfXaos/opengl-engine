This repository demonstrates my progression through Joey de Vries's online book [LearnOpenGL](https://learnopengl.com).
After finishing each chapter, I will update this repository with how I made use of it to improve my opengl-engine.

# [LearnOpenGL](https://learnopengl.com) Chapters Checklist
- [x] I. Getting started
- [x] II. Lighting
- [ ] III. Model Loading
- [ ] IV. Advanced OpenGL
- [ ] V. Advanced Lighting
- [ ] VI. PBR
- [ ] VII. In Practice
- [ ] VIII. 2D Game

# I. Getting started
![utility_header_files](https://user-images.githubusercontent.com/52869398/155899186-1279e767-3527-45f2-a331-469e5aeed998.png)
<p align="center"><i>-Utility Header Files</i></p>

* `shader.h`: reads shader files, then compiles and links them, and prints compile-time errors if found. Contains uniform setter functions.
* `loader.h`: loads models by storing their attributes(vertices, normals, and texture coordinates) each in a VBO(Vertex Buffer Object) and wraps them in a VAO(Vertex Array Object). Loads texture files. 
* `model.h`: stores the loader's outputs which are VAO and texture IDs.
* `renderer.h`: clears color and depth buffers, takes a model to be drawn.
* `display.h`: initializes GLFW and GLAD and terminates the window before the application exits. Handles callback functions. Contains `camera.h` and window propeties.
