#version 150

// In
in vec3 ex_Position;
in vec4 ex_Color;
in vec3 ex_Normal;

// Out
out vec4 out_Color;

// Light Attributes
uniform vec3 LightPosition;
uniform vec3 AmbientLight;
uniform vec3 DiffuseLight;
uniform vec3 SpecularLight;

// Material Attributes
uniform vec3 MaterialAmbient;
uniform vec3 MaterialDiffuse;
uniform vec3 MaterialSpecular;
uniform float MaterialShininess;

// Camera View Vector
uniform vec3 EyeDirection;

// Matrix
uniform mat4 ModelMatrix;
layout(std140) uniform SharedMatrices
{
	mat4 ViewMatrix;
	mat4 ProjectionMatrix;
};


void main(void)
{
	// Blinn-Phong Model
	// Vector Initialization
	vec3 L = normalize(vec3(ViewMatrix * vec4(LightPosition, 1.0)) - ex_Position); //sem view -> luz segue camara, com view -> luz segue cena
	vec3 E = normalize(-EyeDirection);
	vec3 N = normalize(ex_Normal);
	vec3 H = normalize(L + E);

	// Ambient Component
	vec3 ambient = MaterialAmbient * AmbientLight;

	// Diffuse Component
	float NdotL = max(dot(N, L), 0.0);
	vec3 diffuse = MaterialDiffuse * DiffuseLight * NdotL;

	// Specular Component
	vec3 specular = vec3(0.0);
	if(NdotL > 0)
	{
		float NdotH = max(dot(N, H), 0.0);
		specular = MaterialSpecular * SpecularLight * pow(NdotH, MaterialShininess);
	}
	
	//out_Color = vec4(ex_Normal, 1.0);
	out_Color = vec4(ambient + diffuse + specular, 1.0);
}
