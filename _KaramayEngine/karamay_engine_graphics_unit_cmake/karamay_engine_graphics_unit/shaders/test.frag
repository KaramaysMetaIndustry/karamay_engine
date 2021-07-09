#version 460 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 TexCoord;
layout(location = 2) flat in ivec4 test;
layout(location = 3) in vec4 _color;
layout(location = 4) in vec4 _text;

out vec4 FragColor;

uniform sampler2D container2;
uniform sampler2D container3;

uniform vec3 camera_position;
uniform vec4 spe_color;
uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;


layout(std140) uniform Block0
{
	vec4 color0;
	vec3 position0;
};

layout(std140) uniform Block1
{
	vec4 color1;
	vec3 position1;
};

layout(std140) uniform Block2
{
	vec4 color1;
	vec3 position1;
};




void main()
{
   FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}

