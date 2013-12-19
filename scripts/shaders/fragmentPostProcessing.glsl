#version 150

// In
in vec3 ex_Position;
in vec4 ex_Color;
in vec3 ex_Normal;
in vec2 ex_TexCoord;

// Out
out vec4 out_Color;

// Texture Attributes
uniform sampler2D tex;


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


/// 2D Noise by Ian McEwan, Ashima Arts.
	vec3 mod289(vec3 x) { return x - floor(x * (1.0 / 289.0)) * 289.0; }
	vec2 mod289(vec2 x) { return x - floor(x * (1.0 / 289.0)) * 289.0; }
	vec3 permute(vec3 x) { return mod289(((x*34.0)+1.0)*x); }
	
	float snoise (vec2 v) {
		const vec4 C = vec4( 0.211324865405187,  // (3.0-sqrt(3.0))/6.0
			                 0.366025403784439,  // 0.5*(sqrt(3.0)-1.0)
				            -0.577350269189626, // -1.0 + 2.0 * C.x
					         0.024390243902439); // 1.0 / 41.0

		// First corner
		vec2 i  = floor(v + dot(v, C.yy) );
		vec2 x0 = v -   i + dot(i, C.xx);

		// Other corners
		vec2 i1;
		i1 = (x0.x > x0.y) ? vec2(1.0, 0.0) : vec2(0.0, 1.0);
		vec4 x12 = x0.xyxy + C.xxzz;
		x12.xy -= i1;

	   // Permutations
		i = mod289(i); // Avoid truncation effects in permutation
		vec3 p = permute( permute( i.y + vec3(0.0, i1.y, 1.0 )) + i.x + vec3(0.0, i1.x, 1.0 ));

		vec3 m = max(0.5 - vec3(dot(x0,x0), dot(x12.xy,x12.xy), dot(x12.zw,x12.zw)), 0.0);
		m = m*m ;
		m = m*m ;

		// Gradients: 41 points uniformly over a line, mapped onto a diamond.
		// The ring size 17*17 = 289 is close to a multiple of 41 (41*7 = 287)
		vec3 x = 2.0 * fract(p * C.www) - 1.0;
		vec3 h = abs(x) - 0.5;
		vec3 ox = floor(x + 0.5);
		vec3 a0 = x - ox;

		// Normalise gradients implicitly by scaling m
		// Approximation of: m *= inversesqrt( a0*a0 + h*h );
		m *= 1.79284291400159 - 0.85373472095314 * ( a0*a0 + h*h );

		// Compute final noise value at P
		vec3 g;
		g.x  = a0.x  * x0.x  + h.x  * x0.y;
		g.yz = a0.yz * x12.xz + h.yz * x12.yw;
		return 130.0 * dot(m, g);
}

vec4 scratch(){
	float xPeriod = 8.0;
    float yPeriod = 1.0;
    float pi = 3.141592;
    float phase = 0.3;
    float turbulence = snoise(ex_TexCoord * 2.5);
    float vScratch = 0.5 + (sin(((ex_TexCoord.x * xPeriod + ex_TexCoord.y * yPeriod + turbulence)) * pi + phase) * 0.5);
    vScratch = clamp((vScratch * 10000.0) + 0.35, 0.0, 1.0);
	return vec4(vScratch, vScratch, vScratch, 1.0);
}



void main(void) {

	vec4 text = texture(tex, ex_TexCoord);

	// Sepia color
	vec4 sepia_Color = vec4(112.0 / 255.0, 66.0 / 255.0, 20.0 / 255.0, 0.0);
	vec4 final_Color;
	float SepiaValue = 0.7;
	float NoiseValue = 0.1;
	float ScratchValue = 0.3;
	float InnerVignetting = 0.5;
	float OuterVignetting = 1.0;
	float RandomValue = 0.5;

	// SEPIA
		// Grayscale Conversion
		vec4 grayscale = grayscale(text);
		final_Color = grayscale;

		// Overload with sepia color
		final_Color = blend(sepia_Color, grayscale);
		final_Color = grayscale + SepiaValue * (sepia_Color - grayscale);
	

	// NOISE
		float noise = snoise(ex_TexCoord * vec2(800.0 + RandomValue * 600.0,  800.0 + RandomValue * 600.0)) * 0.5;
		final_Color += noise * NoiseValue;

		// Simulate ISO on camera
		vec4 noise_Overlay = blend(final_Color, vec4(noise));
    	final_Color = final_Color + NoiseValue * (final_Color - noise_Overlay);
	
	// SCRATCHES
	float dist = (1.0 / ScratchValue);
    float d = distance(ex_TexCoord, vec2(RandomValue * dist, RandomValue * dist));
    final_Color *= scratch();

	// VIGNETTING
  	float dist1 = distance(vec2(0.5, 0.5), ex_TexCoord) * 1.414213;
    float vignetting = clamp((OuterVignetting - dist1) / (OuterVignetting - InnerVignetting), 0.0, 1.0);
	final_Color *= vignetting;

	
	out_Color = final_Color;
}
