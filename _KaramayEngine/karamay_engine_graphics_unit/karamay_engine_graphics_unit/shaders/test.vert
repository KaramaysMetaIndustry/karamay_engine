#version 450 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in uvec2 cv;

uniform mat4 transform;

out vec2 TexCoord;
out uvec2 acv;

void main()
{
   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
   TexCoord = vec2(aTexCoord.x, aTexCoord.y);
   acv = cv;
}