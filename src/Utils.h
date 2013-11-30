#pragma once

#include <string>
#include <iomanip>
#include "Entity.h"

#define VERTICES 0
#define COLORS 1

#define PR 0.299
#define PG 0.587
#define PB 0.114
#define BR 0.05
#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)<(b))?(a):(b))

namespace Utils {
	
	bool isOpenGLError();

	void checkOpenGLError(std::string error);
	
	char * readFile(char * file);

	GLubyte * index(int vertices);

	Vertex * xmlParser(char * file, int *nVertices);

	void changeColor(float *r, float *g, float *b, float change);
}