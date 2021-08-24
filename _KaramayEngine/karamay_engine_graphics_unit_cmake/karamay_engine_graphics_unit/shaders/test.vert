#version 460 core

#define GLOBAL_PARAMETERS_BEGIN
// define the shader's input
layout(location=0) in vec3 vs_position;
layout(location=1) in vec2 vs_uv;
layout(location=2) in ivec4 vs_kuda;

layout(location=0) out vec3 tescs_position;
layout(location=1) out vec2 tescs_uv;
layout(location=2) out ivec4 tescs_kuma;
layout(location=3) out vec4 tescs_wen;
layout(location=4) out vec4 tescs_ska;


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
	
}
#define MAIN_END