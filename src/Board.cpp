#include "Board.h"

Board::Board(std::string id, char * vertexFile) : Entity(id, vertexFile, false){}

void Board::draw(){
	
	Entity::draw();

}


void Board::update(){}