#version 460 core

uniform struct DirectionalLight
{
	float attenution;
	sampler2D s;
} dir;

struct LightGroup
{
	DirectionalLight directionalLights[10];
	sampler2D a;
};

uniform LightGroup light;

in vec3 position;
in vec2 TexCoord;
flat in ivec4 test;

out vec4 FragColor;

uniform sampler2D container2;
uniform sampler2D container3;

uniform vec3 camera_position;
uniform vec4 spe_color;
uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;

layout(shared) uniform attack
{
	vec4 color12;
	vec3 pos;
	vec4 text;
};

layout(shared) uniform Matrices
{
	vec4 color[5];
};


layout(shared) uniform attack1
{
	vec4 color1;
	vec3 pos1;
	vec4 text1;
};

layout(std430) buffer genda
{
	vec4 st;
	vec4 ps;
	vec4 txt;
};



void main()
{
   //FragColor = vec4(mix(texture(container2, TexCoord), texture(container3, TexCoord), 0.6f).rgb, 1.0f);
   //FragColor = vec4(text + text1);
   //st.r -= 0.00005f;
   //FragColor = vec4((st + txt).rgb + ps.rgb, 1.0f);

   color12.rgb;
}

