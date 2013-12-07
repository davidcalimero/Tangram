#pragma once

#include "Entity.h"

#include <iostream>

class Tabuleiro : public Entity {
	private:
		
	public:
		Tabuleiro(std::string id, char * vertexFile);
		virtual void draw();
		void update();
};
