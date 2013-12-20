#pragma once

#include "Entity.h"
#include "Frame.h"

#include <iostream>

class Board : public Entity {
	private:
		Frame * _base;
		Frame * _left;
		Frame * _right;
		Frame * _front;
		Frame * _back;

	public:
		Board(std::string id);
		virtual ~Board();
		virtual void setTranslation(float x, float y, float z);
		void borderScale(float x, float y, float z);
		void baseScale(float x, float y, float z);
		void setMesh(char * base , char * border, char * mtl);
		virtual void setTexture(char * filename);
		virtual void draw();
		void update();
};
