#include "Board.h"

Board::Board(std::string id) : Entity(id, false){
	_base = new Frame("mesaBase");
	_left = new Frame("mesaMolduraEsquerda");
	_right = new Frame("mesaMolduraDireita");
	_front = new Frame("mesaMolduraFrente");
	_back = new Frame("mesaMolduraTras");
}

Board::~Board() {		
	((Entity *)_base)->~Entity();		
	((Entity *)_left)->~Entity();
	((Entity *)_right)->~Entity();
	((Entity *)_front)->~Entity();
	((Entity *)_back)->~Entity();
}

void Board::setTranslation(float x, float y, float z) {
	_base->setTranslation(x, y, z);
	_left->setTranslation(x - 1.05, y + 0.05, z + 0.05);
	_right->setTranslation(x + 1.05, y - 0.05, z + 0.05);
	_front->setTranslation(x - 0.05, y - 1.05, z + 0.05);
	_back->setTranslation(x + 0.05, y + 1.05, z + 0.05);
}

void Board::borderScale(float x, float y, float z) {
	_left->scale(x, y, z);
	_right->scale(x, y, z);
	_front->scale(y, x, z);
	_back->scale(y, x, z);
}

void Board::baseScale(float x, float y, float z) {
	_base->scale(x, y, z);
}


void Board::draw(){	
	glDisable(GL_STENCIL_TEST);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(1.0f, 1.0);	
	_base->draw();	
	glDisable(GL_POLYGON_OFFSET_FILL);
	_left->draw();	
	_right->draw();	
	_front->draw();	
	_back->draw();
	glEnable(GL_STENCIL_TEST);
}


void Board::setMesh(char * base , char * border, char * mtl){
	_base->setMesh(base, mtl);
	_left->setMesh(border, mtl);
	_right->setMesh(border, mtl);
	_front->setMesh(border, mtl);
	_back->setMesh(border, mtl);
}


void Board::setTexture(char * filename){
	_base->setTexture(filename);
	_left->setTexture(filename);
	_right->setTexture(filename);
	_front->setTexture(filename);
	_back->setTexture(filename);
}


void Board::update(){}


void Board::updateShader(){}