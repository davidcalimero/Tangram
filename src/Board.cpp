#include "Board.h"

Board::Board(std::string id, char * vertexFile, char * mtlFile) : Entity(id, vertexFile, mtlFile, false){
		base = new Frame("mesaBase", "mesh/plane.obj", mtlFile);
		left = new Frame("mesaMolduraEsquerda", vertexFile, mtlFile);
		right = new Frame("mesaMolduraDireita", vertexFile, mtlFile);
		front = new Frame("mesaMolduraFrente", vertexFile, mtlFile);
		back = new Frame("mesaMolduraTras", vertexFile, mtlFile);
}

Board::~Board() {		
		((Entity *)base)->~Entity();		
		((Entity *)left)->~Entity();
		((Entity *)right)->~Entity();
		((Entity *)front)->~Entity();
		((Entity *)back)->~Entity();
}

void Board::setTranslation(float x, float y, float z) {
	base->setTranslation(x, y, z);
	left->setTranslation(x - 1.05, y + 0.05, z + 0.05);
	right->setTranslation(x + 1.05, y - 0.05, z + 0.05);
	front->setTranslation(x - 0.05, y - 1.05, z + 0.05);
	back->setTranslation(x + 0.05, y + 1.05, z + 0.05);
}

void Board::borderScale(float x, float y, float z) {
	left->scale(x, y, z);
	right->scale(x, y, z);
	front->scale(y, x, z);
	back->scale(y, x, z);
}

void Board::baseScale(float x, float y, float z) {
	base->scale(x, y, z);
}


void Board::draw(){	
	glDisable(GL_STENCIL_TEST);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(1.0f, 1.0);	
	base->draw();	
	glDisable(GL_POLYGON_OFFSET_FILL);
	left->draw();	
	right->draw();	
	front->draw();	
	back->draw();
	glEnable(GL_STENCIL_TEST);
}


void Board::update(){}