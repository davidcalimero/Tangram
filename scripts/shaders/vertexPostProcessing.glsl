#version 150

// In
in vec3 in_Position;
in vec2 in_TexCoord;

// Out
out vec2 ex_TexCoord;

void main(void)
{
	ex_TexCoord = in_TexCoord;
	gl_Position = vec4(in_Position, 1.0);
}
