#pragma once

#include "Entity.h"
#include "Input.h"
#include "GameManager.h"

#include <iostream>



class TangramPieces : public Entity {

	private:

	public:
		TangramPieces(std::string id, char * vertexFile);
		void setPos(float px, float py, float pz, glm::quat q);
		void update();
};