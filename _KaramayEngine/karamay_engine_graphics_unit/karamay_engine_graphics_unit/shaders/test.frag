#version 450 core


struct Material
{
	vec4 albedoMap;
	sampler2DArray textures;
};


uniform Material Mat;

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
	vec4 color;
	vec3 pos;
	vec4 text;
};

uniform ax
{
	vec4 css[5];

};

layout(shared) buffer genda
{
	vec4 c;
	vec3 p;
	vec4 t;
};



void main()
{
   //FragColor = vec4(mix(texture(container2, TexCoord), texture(container3, TexCoord), 0.6f).rgb, 1.0f);
   //FragColor = vec4((color.r + text.r), (color.g + text.g), (color.b + text.b), 1.0f);
   FragColor = vec4((color + text).rgb + pos, 1.0f);
   //css.length();
   //uint index;
   //FragColor = texture(Mat.textures, vec3(TexCoord, 0));

}