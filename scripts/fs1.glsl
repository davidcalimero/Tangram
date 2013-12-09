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


void main(void)
{
	// Blinn-Phong Reflexion Model
	// Vector Initialization
	vec3 L = normalize(LightPosition - ex_Position);
	vec3 E = normalize(-EyeDirection);
	vec3 N = normalize(ex_Normal);
	vec3 H = normalize(L + E);

	// Ambient Component
	vec3 ambient = max(vec3(ex_Color) * AmbientLight, vec3(1.0));

	// Diffuse Component
	vec3 diffuse = max(vec3(ex_Color) * DiffuseLight * max(dot(N, L), 0.0), vec3(1.0));

	// Specular Component
	vec3 specular = max(vec3(ex_Color) * SpecularLight * max(dot(N, H), 0.0), vec3(1.0));

	// Sum of Components (can be used, when giving weights to some components. For now, each component has the same weight)
	vec3 final = ambient + diffuse + specular;

	out_Color = vec4(ex_Normal/*final*/, ex_Color.a);
}
