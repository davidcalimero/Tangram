#version 150

in vec3 in_Position;
in vec4 in_Color;
in vec3 in_Normal;

out vec3 ex_Position;
out vec4 ex_Color;
out vec3 ex_Normal;

uniform mat4 ModelMatrix;
uniform mat4 NormalMatrix;

layout(std140) uniform SharedMatrices
{
	mat4 ViewMatrix;
	mat4 ProjectionMatrix;
};

void main(void)
{
	
	ex_Position = vec3(ViewMatrix * ModelMatrix * vec4(in_Position, 1.0));
	ex_Color = in_Color;
	ex_Normal = normalize(vec3(NormalMatrix * vec4(in_Normal, 1.0)));

	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(in_Position, 1.0);
}
