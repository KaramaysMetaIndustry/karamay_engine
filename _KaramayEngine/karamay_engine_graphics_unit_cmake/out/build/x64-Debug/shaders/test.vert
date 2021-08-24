#version 460 core

#define GLOBAL_PARAMETERS_BEGIN
// define the shader's input 
layout (location = 0) in vec3 aPos;
layout (location = 1) in lowp vec2 aTexCoord;
layout (location = 2) in ivec4 atest;
// define the shader's output
layout(location = 0) out vec3 position;
layout(location = 1) out vec2 TexCoord;
layout(location = 2) out ivec4 test;
layout(location = 3) out vec4 _color;
layout(location = 4) out vec4 _text;

// uniforms
layout(std140) uniform att
{
	vec2 ax;
} wat;

layout(std430) buffer stt
{
	vec2 assx;
} ast;

uniform sampler2D texturex[10];
layout(binding = 0, r32f, location = 1) writeonly uniform image1D positionImage1D;
layout(binding = 0, r32f, location = 2) coherent uniform image1D normalImage1D;
layout(binding = 0, offset = 4) uniform atomic_uint counter;
#define GLOBAL_PARAMETERS_END 


#define GLOBAL_FUNCTIONS_BEGIN

#define GLOBAL_FUNCTIONS_END


#define MAIN_BEGIN
void main()
{
//   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
//   
//   TexCoord = vec2(aTexCoord.x, aTexCoord.y);
//   test = atest;
//
//   vec2 x = imageLoad(input_image, int(0)).xy;
//   a.REX;
}
#define MAIN_END