#version 150

// In
in vec3 ex_Position;
in vec4 ex_Color;
in vec3 ex_Normal;
in vec2 ex_TexCoord;
in vec3 mc_Position;

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


// Texture Sample
uniform sampler2D tex; //NOISE
uniform float withTexture;

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
	vec3 tst = vec3(1.0);

	/*   WOOD STAYLE   */
	if(withTexture == 1){
		vec3 darkWood = vec3(139.0/255.0, 69.0/255.0, 19.0/255.0);
		vec3 lightWood = vec3(222.0/255.0, 184.0/255.0, 135.0/255.0);
		float ringFrequency = 6.72;
		float ringSharpness = 21.0;
		float ringScale = 0.5;

		float noiseScale = 1.0;

		vec2 scaled_pos = ex_TexCoord * noiseScale;

		float signed_noise = 2.0 * texture(tex, scaled_pos).r - 1.0;

		float frp = fract(scaled_pos.y * ringFrequency + ringScale * signed_noise);

		float invMax = pow(ringSharpness, ringSharpness / (ringSharpness - 1.0)) / (ringSharpness - 1.0);

		float ring = invMax * (frp - pow(frp , ringSharpness));

		float lrp = ring + signed_noise;

		tst = mix(darkWood, lightWood , lrp);
	}


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
	
	vec4 LightIntensity = vec4(((ambient + diffuse) * tst) + specular, 1.0);

	//out_Color = vec4(ex_Normal, 1.0);
	//out_Color = texture(tex, ex_TexCoord) * out_Color;
	out_Color = vec4(tst, 1.0) * LightIntensity;
}
