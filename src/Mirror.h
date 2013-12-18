#pragma once

#include "Entity.h"

#include <iostream>

class Mirror : public Entity {
	private:
		
	public:
		Mirror(std::string id, char * vertexFile, char * mtlFile);
		virtual void draw();
		void update();
};
