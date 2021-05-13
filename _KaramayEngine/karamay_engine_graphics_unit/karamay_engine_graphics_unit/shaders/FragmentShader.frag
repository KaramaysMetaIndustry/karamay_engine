#version 330 core
struct Material
{
	vec3 Ambient;
	sampler2D Diffuse;
	sampler2D Specular;
	float Shininess;
};

struct PointLight{
	float Constant;
	float Linear;
	float Quadratic;
};

struct SpotLight{
	float cosPhy;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

out vec4 FragColor;

uniform Material material;
uniform PointLight pointLight;
uniform SpotLight spotLight;

uniform vec3 ObjectReflectionAbility;
uniform vec3 AmbientLightColor;

uniform vec3 LightPosition;
uniform vec3 LightColor;
uniform vec3 DirectionalLightDirection;
uniform vec3 CameraPosition;

void main()
{	
	float Distance = length(LightPosition - FragPos);
	float Attenuation = 1.0 / (pointLight.Constant + pointLight.Linear * Distance + pointLight.Quadratic * (Distance * Distance));

	vec3 LightDirection = normalize(DirectionalLightDirection);
	//normalize(DirectionalLightDirection);
	vec3 ReflectVec = reflect(-LightDirection, Normal);
	vec3 CameraVec = normalize(CameraPosition - FragPos);

	vec3 Ambient 
	= texture(material.Diffuse, TexCoord).rgb * AmbientLightColor;

	vec3 Diffuse 
	= texture(material.Diffuse, TexCoord).rgb * max(dot(LightDirection, Normal), 0) * LightColor; 

	vec3 Specular 
	= texture(material.Specular, TexCoord).rgb * pow(max(dot(CameraVec,  ReflectVec), 0), 64) * LightColor;

	float cosTheta = dot(normalize(FragPos - LightPosition), -1 * LightDirection);

	if(cosTheta > spotLight.cosPhy)
	{	
		FragColor = vec4((Ambient + (Diffuse + Specular)), 1.0);
	}else{
		FragColor = vec4((Ambient), 1.0);
	}

	
}