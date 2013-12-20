#version 150

// In
in vec2 ex_TexCoord;

// Out
out vec4 out_Color;

// Texture Attributes
uniform sampler2D tex;

// Auxiliar Attributes
uniform int width;
uniform int height;
uniform int effect;

// Blending two colors
vec4 blend(vec4 src, vec4 dst){
 	return vec4( (dst.x <= 0.5) ? (2.0 * src.x * dst.x) : (1.0 - 2.0 * (1.0 - dst.x) * (1.0 - src.x)),
	   	         (dst.y <= 0.5) ? (2.0 * src.y * dst.y) : (1.0 - 2.0 * (1.0 - dst.y) * (1.0 - src.y)),
        	     (dst.z <= 0.5) ? (2.0 * src.z * dst.z) : (1.0 - 2.0 * (1.0 - dst.z) * (1.0 - src.z)),
	      	 0.0);
}

// Apply Perceptual Grayscale
vec4 grayscale(vec4 color){
	float avg = 0.2126 * color.x + 0.7152 * color.y + 0.0722 * color.z;

	return vec4(avg, avg, avg, 1.0);
}

// Apply Sepia
vec4 sepia(vec4 color, float SepiaValue){
	vec4 sepia_Color = vec4(112.0 / 255.0, 66.0 / 255.0, 20.0 / 255.0, 0.0);
	vec4 grayscale = grayscale(color);
	vec4 temp = blend(sepia_Color, grayscale);
	return (temp + SepiaValue * (sepia_Color - temp));
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

// Apply noise - falta os tamanhos
vec4 noise(vec4 color, float NoiseValue, float RandomValue){
	float noise = snoise(ex_TexCoord * vec2(1280 + RandomValue * 800,  1280 + RandomValue * 800)) * 0.5;
	return (color + (noise * NoiseValue));
}

vec4 noiseandiso(vec4 color, float NoiseValue, float RandomValue){
	vec4 noise = noise(color, NoiseValue, RandomValue);
	vec4 noise_Overlay = blend(color, vec4(noise));
    return (noise + NoiseValue * (noise - noise_Overlay));
}


vec4 scratch_aux(){
	float xPeriod = 8;
    float yPeriod = 0;
    float pi = 3.141592;
    float phase = 1;
    float turbulence = 0;
	// snoise(ex_TexCoord *	0.69);
    float vScratch = 0.5 + (sin(((ex_TexCoord.x * xPeriod + ex_TexCoord.y * yPeriod + turbulence)) * pi + phase) * 0.5);
    vScratch = clamp((vScratch * 10.0) + 0.65, 0.0, 1.0);
	return vec4(vScratch, vScratch, vScratch, 1.0);
}

vec4 scratchs(vec4 tex, float ScratchValue, float RandomValue){ 
	float dist = (1.0 / ScratchValue);
	float d = distance(ex_TexCoord, vec2(RandomValue * dist, RandomValue * dist));
	if(d < 0.69) return (tex *= scratch_aux());
	else return tex;
}

vec4 vignetting(vec4 tex, float InnerVignetting, float OuterVignetting){
  	float dist1 = distance(vec2(0.5, 0.5), ex_TexCoord) * 1.414213;
	float vignetting = clamp((OuterVignetting - dist1) / (OuterVignetting - InnerVignetting), 0.0, 1.0);
	return tex*= vignetting;
}


void main(void) {

	vec4 text = texture(tex, ex_TexCoord);
	vec4 final_Color = text;
	
	float SepiaValue = 0.7;
	float NoiseValue = 0.1;
	float RandomValue = 1;
	float ScratchValue = 4;
	float InnerVignetting = 0.6;
	float OuterVignetting = 1.0;

	switch(effect){
		case 1: // Grayscale
			final_Color = grayscale(final_Color);
			break;
		case 2: // Sepia 
			final_Color = sepia(final_Color, SepiaValue);
			break;
		case 3: // Noise
			final_Color = noise(final_Color, NoiseValue, RandomValue);
			break;
		case 4: // Vignetting
			final_Color = vignetting(final_Color, InnerVignetting, OuterVignetting);
			break;
		case 5: // Special 1
			final_Color = grayscale(final_Color);
			final_Color = noise(final_Color, NoiseValue, RandomValue);
			// final_Color = scratchs(final_Color, ScratchValue, RandomValue);
			final_Color = vignetting(final_Color, InnerVignetting, OuterVignetting);
			break;
      break;
   }

	out_Color = final_Color;
}
