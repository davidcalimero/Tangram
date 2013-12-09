#pragma once

#include "ProgramShader.h"
#include <glm.hpp>
#include <ext.hpp>

class Light
{
	private:
		glm::vec3 _ambientColor;
		glm::vec3 _diffuseColor;
		glm::vec3 _specularColor;
		glm::vec3 _position;

	public:
		Light(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
		void setShaderLightValues();
};

