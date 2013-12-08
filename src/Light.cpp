#include "Light.h"

Light::Light(void){

}

Light::Light(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular){
	_position = position;
	_ambientColor = ambient;
	_diffuseColor = diffuse;
	_specularColor = specular;
}

Light::~Light(void){

}

void Light::setShaderLightValues(){
	GLuint ambientId, diffuseId, specularId, positionId;
	glUseProgram(ProgramShader::getInstance()->getProgramId());

	// Get IDs
	positionId = ProgramShader::getInstance()->getId("LightPosition");
	ambientId = ProgramShader::getInstance()->getId("AmbientLight");
	diffuseId = ProgramShader::getInstance()->getId("DiffuseLight");
	specularId = ProgramShader::getInstance()->getId("SpecularLight");

	// Set Values
	glUniform3fv(positionId, 1, glm::value_ptr(_position));
	glUniform3fv(ambientId, 1, glm::value_ptr(_ambientColor));
	glUniform3fv(diffuseId, 1, glm::value_ptr(_diffuseColor));
	glUniform3fv(specularId, 1, glm::value_ptr(_specularColor));

	glUseProgram(0);
}