#pragma once

#include "Entity.h"

#include <iostream>

class Mirror : public Entity {
	private:
		
	public:
		Mirror(std::string id);
		virtual void draw();
		void update();
		void updateShader();
};
