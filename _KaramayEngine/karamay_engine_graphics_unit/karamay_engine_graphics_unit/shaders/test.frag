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


uniform struct Material
{
	sampler2D texture0;
} mats[2];


struct Light
{
	vec4 color;
	vec3 direction;
} a;



layout(shared) uniform attack
{
	vec4 color;
	vec3 pos;
	vec4 text[];
	Light l;
} at[];


layout(shared) uniform attack1
{
	vec4 color1;
	vec3 pos1;
	vec4 text1;
};



uniform Material0{
	sampler2D texture0;
} mat0;


uniform struct Material1
{
	//vec4 a;
	sampler2D texture1;
} wa;


layout(std430) buffer wida
{
	vec4 a[];
} ad[];




void main()
{
   //FragColor = vec4(mix(texture(container2, TexCoord), texture(container3, TexCoord), 0.6f).rgb, 1.0f);
   //FragColor = vec4(text + text1);
   //st.r -= 0.00005f;
   
}

