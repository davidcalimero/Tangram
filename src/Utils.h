#pragma once

#include "GL/glew.h"
#include "GL/freeglut.h"

#include "ProgramShader.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <ctime>
#include <rapidxml.hpp>
#include <rapidxml_print.hpp>
#include <gtc/quaternion.hpp>
#include <SOIL.h>

#define VERTICES 0
#define COLORS 1
#define NORMALS 2
#define UVS 3

#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)<(b))?(a):(b))
#define SWAP(T, a, b) {T temp = a; a = b; b = temp;}

typedef struct {
	GLfloat XYZW[4];
	GLfloat RGBA[4];
} Vertex;

namespace Utils {
	
	bool isOpenGLError();
	void checkOpenGLError(std::string error);	
	char * readFile(char * file);
	int screenshot(std::string _filename, int _width, int _height); // 
	std::string date_time(); //
	void loadScene(char * file, std::string id, glm::quat * quaternion, glm::vec3 * position);
	void saveScene(char * file, std::string id, glm::quat quaternion, glm::vec3 position);
	void loadObj(char* filename, std::vector<unsigned int> &indices, std::vector<glm::vec3> &out_vertices, std::vector<glm::vec2> &out_uvs, std::vector<glm::vec3> &out_normals);
	void loadMaterial(char* filename, glm::vec3 &ambient, glm::vec3 &diffuse, glm::vec3 &specular, float &shininess, std::string &texture);
}
