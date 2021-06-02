#version 450 core
out vec4 FragColor;

in vec2 TexCoord;
in uvec2 acv;

uniform sampler2D container2;
uniform vec3 uniform0;
uniform vec4 uniform1;

void main()
{
   FragColor = vec4(acv.x, 0.0f, 0.0f, 1.0f);
   //FragColor = vec4(uniform1.rgba);
   //FragColor = mix(texture(container2, TexCoord), texture(albedo_map, TexCoord), 0.2);
   //FragColor = vec4(TexCoord.x, TexCoord.y, 0.0f, 1.0f);
   //FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord));
}