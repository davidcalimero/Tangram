#pragma once

#include "Utils.h"

#include <iostream>
#include <glm.hpp>
#include <vector>

class Mesh {
	private:
		GLuint _vaoId;
		GLuint _vbo[4];
		std::vector<unsigned int> _indices;
		std::vector<glm::vec3> _vertices;
		std::vector<glm::vec2> _uvs;
		std::vector<glm::vec3> _normals;
		
	public:
		Mesh(char * objFile);
		~Mesh();
		void draw();
};