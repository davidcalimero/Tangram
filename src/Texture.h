#pragma once

#include "Utils.h"

#include <iostream>
#include <glm.hpp>
#include <SOIL.h>

#include "GL/glew.h"
#include "GL/freeglut.h"

class Texture {
	private:

		GLuint _textureID;
		std::string _textureName;
		float _animationTryOut;
		float _selected;

	public:
		Texture(std::string textureName);
		~Texture();
		void bind();
		void unbind();
		void activateAnimation();
		void desactivateAnimation();
};