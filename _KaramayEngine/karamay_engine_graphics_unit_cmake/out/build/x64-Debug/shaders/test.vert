#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in lowp vec2 aTexCoord;
layout (location = 2) in ivec4 atest;

layout(location = 0) out vec3 position;
layout(location = 1) out vec2 TexCoord;
layout(location = 2) out ivec4 test;
layout(location = 3) out vec4 _color;
layout(location = 4) out vec4 _text;

layout(std140) uniform att
{
	vec2 ax;
};


uniform sampler2D texturex[10];
uniform writeonly image1D imagex;
layout (binding = 0, r32f, location = 1) coherent uniform image1D input_image;

uniform mat4 transform;

void main()
{
   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);

   TexCoord = vec2(aTexCoord.x, aTexCoord.y);
   test = atest;

   float x = imageLoad(input_image, int(0)).x;

}