#include "Board.h"

Board::Board(std::string id, char * vertexFile, char * mtlFile) : Entity(id, vertexFile, mtlFile, false){}

void Board::draw(){
	
	Entity::draw();

}


void Board::update(){}