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

vec4 grayscale(vec4 color){
	float avg = 0.2126 * color.x + 0.7152 * color.y + 0.0722 * color.z;
	return vec4(avg, avg, avg, 0.0);
}

vec4 blend(vec4 src, vec4 dst){
 return vec4( (dst.x <= 0.5) ? (2.0 * src.x * dst.x) : (1.0 - 2.0 * (1.0 - dst.x) * (1.0 - src.x)),
              (dst.y <= 0.5) ? (2.0 * src.y * dst.y) : (1.0 - 2.0 * (1.0 - dst.y) * (1.0 - src.y)),
              (dst.z <= 0.5) ? (2.0 * src.z * dst.z) : (1.0 - 2.0 * (1.0 - dst.z) * (1.0 - src.z)),
              0.0);

}


void main(void)
{

	// Sepia color
	vec4 sepia_Color = vec4(112.0 / 255.0, 66.0 / 255.0, 20.0 / 255.0, 0.0);


	// LIGHTS 
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

		vec4 light_Color = vec4(ambient + diffuse + specular, 1.0);


	// SEPIA
		// Grayscale Conversion
		vec4 grayscale = grayscale(light_Color);

		// Overload with sepia color
		vec4 final_Color = blend(sepia_Color, grayscale);
		final_Color = grayscale + 0.5 /* ?? */ * (sepia_Color - grayscale);
	
	// NOISE


	// SCRATCHES


	// VIGNETTING


	out_Color = final_Color;
}
