#pragma once

#include "Entity.h"

#include <iostream>
#include <gtc/quaternion.hpp>

class Axis : public Entity {
	private:
		glm::vec3 _direction;

	public:
		Axis(std::string id, char * vertexFile);
		glm::vec3 returnTranslateVector();
		void setTranslateVector(glm::vec3 direction);
		void setPosition(float px, float py, float pz);
		void update();
};

