#version 450 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in lowp vec2 aTexCoord;
layout (location = 2) in ivec4 atest;



out ivec4 test;

uniform mat4 transform;

out vec2 TexCoord;




in vec3 a2;
in vec3 a3;
in vec3 a4;
in vec3 a5;
in vec3 a6;


void main()
{
   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
   TexCoord = vec2(aTexCoord.x, aTexCoord.y);
   test = atest;
}