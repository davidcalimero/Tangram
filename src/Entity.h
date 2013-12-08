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



class Entity {

	private:
		GLuint _vaoId;
		GLuint _vboId[2];
		int _nVertices;
		glm::quat _q;
		glm::mat4 _matrix;
		Vertex * _vertices;
		bool _reflection;
		float _height;

	protected:
		float _px, _py, _pz;
		std::string _id;
		Entity(std::string id, char * vertexFile, bool reflection);

	public:
		~Entity();
		virtual void update() = 0;
		virtual void draw();
		glm::vec3 getPos();
		std::string getId();
		void setRotation(glm::quat q);
		void rotate(float x, float y, float z, float angle);
		void translate(float x, float y, float z);
		void scale(float x, float y, float z);
		void shear(float x, float y);
		void lerp(float x, float y, float z, float k);
};