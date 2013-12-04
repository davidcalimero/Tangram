#pragma once

#include "Entity.h"

#include <iostream>
#include <gtc/quaternion.hpp>



class TangramPieces : public Entity {

	private:

	public:
		TangramPieces(std::string id, char * vertexFile);
		void setPos(float px, float py, float pz, float rz);
		void update();
};