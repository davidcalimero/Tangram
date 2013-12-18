#pragma once

#include "Utils.h"

#include <iostream>
#include <glm.hpp>
#include <ext.hpp>
#include <vector>

class Mesh {
	private:
		GLuint _vaoId;
		GLuint _vbo[4];
		std::vector<unsigned int> _indices;
		std::vector<glm::vec3> _vertices;
		std::vector<glm::vec2> _uvs;
		std::vector<glm::vec3> _normals;
		glm::vec3 _ambientColor;
		glm::vec3 _diffuseColor;
		glm::vec3 _specularColor;
		float _shininess;
		std::string _texture;
		GLuint _tex;
		
	public:
		Mesh(char * objFile, char * mtlFile);
		~Mesh();
		void draw();
};