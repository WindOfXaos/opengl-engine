#ifndef LIGHT_H
#define LIGHT_H

#include <glm/vec3.hpp>

struct Material
{
    float shininess;
    float reflectivity; 
};

struct DirLight 
{
    glm::vec3 direction;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular; 
};  

struct PointLight 
{   
    // positions of the point lightPos
    unsigned int N;
    glm::vec3 *positions;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    float constant; 
    float linear;
    float quadratic;
};

#endif
