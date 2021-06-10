#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in lowp vec2 aTexCoord;
layout (location = 2) in ivec4 atest;

out vec3 position;
out vec2 TexCoord;
out ivec4 test;

uniform mat4 transform;

void main()
{
   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
   position = aPos;
   TexCoord = vec2(aTexCoord.x, aTexCoord.y);
   test = atest;
}