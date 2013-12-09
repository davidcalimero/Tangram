#version 150

in vec3 ex_Position;
in vec4 ex_Color;
in vec3 ex_Normal;

out vec4 out_Color;

// Light Attributes
uniform vec3 LightPosition;
uniform vec3 AmbientLight;
uniform vec3 DiffuseLight;
uniform vec3 SpecularLight;

// Material Shininess
uniform float Shininess;

// Camera View Vector
uniform vec3 EyeDirection;

uniform mat4 ModelMatrix;

layout(std140) uniform SharedMatrices
{
	mat4 ViewMatrix;
	mat4 ProjectionMatrix;
};


void main(void)
{
	// Blinn-Phong Reflexion Model
	// Vector Initialization
	vec3 L = normalize(vec3(ViewMatrix * ModelMatrix * vec4(LightPosition, 1.0)) - ex_Position);
	vec3 E = normalize(-EyeDirection);
	vec3 N = normalize(ex_Normal);
	vec3 H = normalize(L + E);

	// Ambient Component
	vec4 ambient = vec4(AmbientLight, 1.0);

	// Diffuse Component
	float NdotL = max(dot(N, L), 0.0);
	vec4 diffuse = vec4(DiffuseLight, 1.0) * NdotL;

	// Specular Component
	vec4 specular = vec4(0.0);
	if(NdotL > 0)
	{
		float NdotH = max(dot(N, H), 0.0);
		specular = vec4(SpecularLight, 1.0) /** pow(NdotH, Shininess)*/;
	}
	
	out_Color = vec4(ex_Normal, 1.0);
	//out_Color = ambient + diffuse + specular;
}
