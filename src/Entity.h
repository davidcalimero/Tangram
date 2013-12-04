#pragma once

#include "GL/glew.h"
#include "GL/freeglut.h"

#include "Utils.h"
#include "ProgramShader.h"

#include <gtc/matrix_transform.hpp>
#include <gtx/transform2.hpp>
#include <gtc/quaternion.hpp>
#include <glm.hpp>
#include <string>
#include <iostream>
#include <cmath>



class Entity {

	private:
		glm::mat4 _matrix;
		GLuint _vaoId;
		GLuint _vboId[2];
		int _nVertices;
		Vertex * _vertices;
		glm::quat _q;
		glm::quat _qr;
		bool _reflection;

	protected:
		float _px, _py, _pz;
		std::string _id;
		Entity(std::string id, char * vertexFile, bool reflection);

	public:
		~Entity();
		virtual void update() = 0;
		void draw();
		glm::vec3 getPos();
		std::string getId();
		void rotate(float x, float y, float z, float angle);
		void translate(float x, float y, float z);
		void scale(float x, float y, float z);
		void shear(float x, float y);
		void lerp(float x, float y, float z, float k);
		void slerp(glm::quat q, float k);
};