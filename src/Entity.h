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
		Entity(std::string id, char * objFile, char * mtlFile, bool reflection);

	public:
		virtual ~Entity();
		virtual void update() = 0;
		virtual void draw();
		void drawReflection();
		glm::vec3 getPos();
		glm::quat getQuat();
		std::string getId();
		Mesh * getMesh();
		void setRotation(glm::quat q);
		void setTranslation(float x, float y, float z);
		void rotate(float x, float y, float z, float angle);
		void translate(float x, float y, float z);
		void scale(float x, float y, float z);
		void shear(float x, float y);
		void lerp(float x, float y, float z, float k);

		void activateAnimation();
		void desactivateAnimation();
};