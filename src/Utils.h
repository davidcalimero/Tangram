#pragma once

#include "GL/glew.h"
#include "GL/freeglut.h"

#include "ProgramShader.h"

#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <map>
#include <list>
#include <vector>
#include <glm.hpp>
#include <sstream>
#include <rapidxml.hpp>
#include <rapidxml_print.hpp>
#include <gtc/quaternion.hpp>

#define VERTICES 0
#define COLORS 1

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
	GLubyte * index(int vertices);
	Vertex * xmlParser(char * file, int *nVertices);
	void loadScene(char * file, std::string id, glm::quat * quaternion, glm::vec3 * position);
	void saveScene(char * file, std::string id, glm::quat quaternion, glm::vec3 position);
	void loadObj(char* filename);
}