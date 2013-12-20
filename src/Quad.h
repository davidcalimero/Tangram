#pragma once

#include "Utils.h"
//#include "Texture.h"
#include "Entity.h"

#include <iostream>
#include <glm.hpp>
#include <SOIL.h>

#include "GL/glew.h"
#include "GL/freeglut.h"

class Quad : public Entity {
	private:
		GLuint texColorBufferPP;
		GLuint rboStencilDepthPP;
			
		void bind();
		

	public:
		Quad(std::string id);
		void init();
		void predraw();
		void draw();
		void update();
};