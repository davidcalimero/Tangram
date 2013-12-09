#include "Light.h"


Light::Light(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular){
	_position = position;
	_ambientColor = ambient;
	_diffuseColor = diffuse;
	_specularColor = specular;
}

void Light::setShaderLightValues(){
	// Get IDs
	GLint positionId = ProgramShader::getInstance()->getId("LightPosition");
	GLint ambientId = ProgramShader::getInstance()->getId("AmbientLight");
	GLint diffuseId = ProgramShader::getInstance()->getId("DiffuseLight");
	GLint specularId = ProgramShader::getInstance()->getId("SpecularLight");

	// Set Values
	glUniform3fv(positionId, 1, glm::value_ptr(_position));
	glUniform3fv(ambientId, 1, glm::value_ptr(_ambientColor));
	glUniform3fv(diffuseId, 1, glm::value_ptr(_diffuseColor));
	glUniform3fv(specularId, 1, glm::value_ptr(_specularColor));
}