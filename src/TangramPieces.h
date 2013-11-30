#pragma once

#include "Entity.h"
#include <gtc/quaternion.hpp>

class TangramPieces : public Entity {

	private:
		float _px1, _py1, _pz1;
		glm::quat  _r1;
		float _px2, _py2, _pz2;
		glm::quat _r2;

	public:
		TangramPieces(std::string id, char * vertexFile);

		void setPos1(float px, float py, float pz, float rz);

		void setPos2(float px, float py, float pz, float rz);

		void swapPos();

		void update();
};