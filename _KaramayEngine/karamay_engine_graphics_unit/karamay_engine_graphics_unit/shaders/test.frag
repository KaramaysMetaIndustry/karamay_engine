#version 450 core

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

layout(packed) uniform attack
{
	vec4 color;
	vec3 pos;
	vec4 text;
};



void main()
{
   //FragColor = vec4(mix(texture(container2, TexCoord), texture(container3, TexCoord), 0.6f).rgb, 1.0f);
   //FragColor = vec4((color.r + text.r), (color.g + text.g), (color.b + text.b), 1.0f);
   FragColor = vec4(pos, 1.0f);
}