#pragma once

#include "GL/glew.h"
#include "GL/freeglut.h"
#include <gtc/quaternion.hpp>

class Camera {

	private:
		glm::quat _q;
		GLuint _vboUBId;
		bool _type;
		Camera();

	public:
		~Camera();
		static Camera * getInstance();
		void put(float racio);
		void rotate(float angleX, float angleZ);
		void change();
};