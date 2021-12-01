#version 330 core
out vec4 FragColor;

in vec2 TextCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform vec3 lightColor;

void main()
{
    FragColor = mix(texture(texture1, TextCoord), texture(texture2, TextCoord), 0.2) * vec4(lightColor * 1.5, 1.0);
}