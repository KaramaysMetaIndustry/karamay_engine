#version 460 core
#extension GL_ARB_bindless_texture : require
#extension GL_ARB_shading_language_include : require

#include "/common.glsl" //! #include "common.glsl"

#pragma STDGL invariant(all)
#pragma optimize(on)
#pragma debug(on)

#define _PAMATERS

#ifdef _PAMATERS

layout(binding = 0, std430) buffer GlobalBuffer
{
	vec4 aa;
	layout(r32f) image1D readBackPosition1;
};

#endif

//----------------------------
//float GetTessLevel(float distance0, float distance1);

uniform vec3 camera_position;

//----------------------------
layout(vertices = 3) out;

layout(location = 0) in vec3 tesc_position[];
layout(location = 1) in vec2 tesc_uv[];
layout(location = 2) in vec3 tesc_normal[];

layout(location = 0) out vec3 tese_position[];
layout(location = 1) out vec2 tese_uv[];
layout(location = 2) out vec3 tese_normal[];


void main()
{
	tese_position[gl_InvocationID] = tesc_position[gl_InvocationID];
	tese_normal[gl_InvocationID] = tesc_normal[gl_InvocationID];
	tese_uv[gl_InvocationID] = tesc_uv[gl_InvocationID];

	float distance0 = distance(camera_position, tesc_position[0]); 
	float distance1 = distance(camera_position, tesc_position[1]); 
	float distance2 = distance(camera_position, tesc_position[2]); 

	if (gl_InvocationID == 0)
	{
		gl_TessLevelOuter[0] = GetTessLevel(distance1, distance2);
		gl_TessLevelOuter[1] = GetTessLevel(distance2, distance0);
		gl_TessLevelOuter[2] = GetTessLevel(distance0,distance1);
		gl_TessLevelInner[0] = gl_TessLevelOuter[2];
	}
}

//float GetTessLevel(float distance0, float distance1)
//{
//	float avg_distance = (distance0 + distance1) / 2;
//	// if(avg_distance <= 2.0)
//	// {
//	// 	return 100.0;
//	// }
//	// else if(avg_distance <= 5.0)
//	// {
//	// 	return 7.0;
//	// }
//	// else
//	// {
//	// 	return 3.0;
//	// }
//
//	return 100;
//}

