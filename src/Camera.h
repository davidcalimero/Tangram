#pragma once

#include "GL/glew.h"
#include "GL/freeglut.h"

#include <iostream>
#include <gtc/matrix_transform.hpp>
#include <gtc/quaternion.hpp>
#include <glm.hpp>



class Camera {

	private:
		glm::quat _q;
		glm::vec3 _eye;
		glm::vec3 _center;
		glm::vec3 _up;
		int _angleX;
		int _angleZ;
		GLuint _vboUBId;
		bool _type;
		Camera();

	public:
		~Camera();
		static Camera * getInstance();
		void put(float racio);
		void rotate(int angleX, int angleZ);
		void change();
		glm::vec3 getCameraAngles();

		//void getCameraRef(glm::vec3 & s, glm::vec3 & v, glm::vec3 & u);

};