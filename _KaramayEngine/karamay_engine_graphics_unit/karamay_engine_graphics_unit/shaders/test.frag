#version 450 core

in vec3 position;
in vec2 TexCoord;
flat in ivec4 test;

out vec4 FragColor;

uniform vec3 uniform0;
uniform vec4 uniform1;
uniform sampler2D container2;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;


void main()
{
   FragColor = vec4(texture(container2, TexCoord).rgb, 1.0f);
}