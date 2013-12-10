#pragma once

#include "Utils.h"
#include "Mesh.h"

#include <gtx/transform2.hpp>
#include <glm.hpp>
#include <iostream>



class Entity {

	private:
		glm::quat _q;
		glm::mat4 _matrix;
		bool _reflection;
		float _height;
		Mesh * _mesh;

	protected:
		float _px, _py, _pz;
		std::string _id;
		Entity(std::string id, char * objFile, bool reflection);

	public:
		~Entity();
		virtual void update() = 0;
		virtual void draw();
		glm::vec3 getPos();
		glm::quat getQuat();
		std::string getId();
		void resetPos(float x, float y, float z, glm::quat q);
		void setRotation(glm::quat q);
		void setTranslation(float x, float y, float z);
		void rotate(float x, float y, float z, float angle);
		void translate(float x, float y, float z);
		void scale(float x, float y, float z);
		void shear(float x, float y);
		void lerp(float x, float y, float z, float k);
};