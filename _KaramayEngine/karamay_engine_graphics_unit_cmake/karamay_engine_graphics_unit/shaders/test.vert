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

layout(binding = 0, r32f, location = 1) writeonly uniform image1D positionImage1D;
layout(binding = 0, r32f, location = 2) coherent restrict uniform image1DArray normalImage1Ds;
layout(binding = 0, offset = 4) uniform atomic_uint counter;
layout(binding = 0, offset = 8) uniform atomic_uint counter1;

layout(binding = 0) uniform sampler2DArray ass;
layout(binding = 0) uniform sampler2DArray ass1;

shared 

#define GLOBAL_PARAMETERS_END

#define GLOBAL_FUNCTIONS_BEGIN

#define GLOBAL_FUNCTIONS_END

#define MAIN_BEGIN
void main()
{
	imageLoad(normalImage1Ds, ivec2(0, 0));
	//400-666-8800
}
#define MAIN_END