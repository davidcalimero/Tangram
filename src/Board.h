#pragma once

#include "Entity.h"

#include <iostream>

class Board : public Entity {
	private:
		
	public:
		Board(std::string id, char * vertexFile);
		virtual void draw();
		void update();
};
