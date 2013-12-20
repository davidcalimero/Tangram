#pragma once

#include "Utils.h"
#include "Mesh.h"
#include "Texture.h"

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
		Texture * _texture;

	protected:
		float _px, _py, _pz;
		std::string _id;
		Entity(std::string id, bool reflection);

	public:
		virtual ~Entity();
		virtual void update() = 0;
		virtual void draw();
		void drawReflection();
		glm::vec3 getPos();
		glm::quat getQuat();
		std::string getId();
		void setMesh(char * filename, char * mtl);
		virtual void setTexture(char * filename);
		virtual void updateShader() = 0;
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