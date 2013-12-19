#pragma once

#include "Entity.h"
#include "Frame.h"

#include <iostream>

class Board : public Entity {
	private:
		Frame * base;
		Frame * left;
		Frame * right;
		Frame * front;
		Frame * back;

	public:
		Board(std::string id, char * vertexFile, char * mtlFile);
		virtual ~Board();
		virtual void setTranslation(float x, float y, float z);
		void borderScale(float x, float y, float z);
		void baseScale(float x, float y, float z);
		virtual void draw();
		void update();
};
