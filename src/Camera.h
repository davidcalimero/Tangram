#pragma once

#include "GL/glew.h"
#include "GL/freeglut.h"

#include <iostream>
#include <gtc/matrix_transform.hpp>
#include <gtx/rotate_vector.hpp>
#include <gtc/quaternion.hpp>
#include <glm.hpp>
#include <algorithm>



class Camera {

	private:
		glm::quat _q;
		glm::vec3 _eye;
		glm::vec3 _center;
		glm::vec3 _up;
		GLuint _vboUBId;
		bool _type;
		Camera();
		glm::mat4 _view;
		int _distance;

	public:
		~Camera();
		static Camera * getInstance();
		void put(float racio);
		void rotate(int angleX, int angleZ);
		void change();
		glm::vec3 getCameraAngles();
		glm::mat4 getView();
		void addToDistance(int amount);

};