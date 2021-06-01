#version 450 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D container2;
uniform sampler2D texture2;

void main()
{
   //FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
   FragColor = texture(container2, TexCoord);
   //FragColor = vec4(TexCoord.x, TexCoord.y, 0.0f, 1.0f);
   //FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord));
}