#version 330 core
out vec4 FragColor;

in vec2 TextCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mixing;

uniform vec3 lightColor;
uniform vec3 lightPos;


void main()
{
   //calculate denisty based on angle between normals and light position
   //-------------------------------------------------------------------
   // ambient
   float ambientStrength = 0.2f;
   vec3 ambient = ambientStrength * lightColor;

   // diffuse
   vec3 norm = normalize(Normal);
   vec3 lightDir = normalize(lightPos - FragPos);   
   float diff = max(dot(norm, lightDir), 0.0);
   vec3 diffuse = diff * lightColor;

   vec3 result = (ambient + diffuse);
   FragColor = mix(texture(texture1, TextCoord), texture(texture2, TextCoord), mixing) * vec4(result, 1.0) * vec4(lightColor * 1.5, 1.0);  
}