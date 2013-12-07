#include "Tabuleiro.h"

Tabuleiro::Tabuleiro(std::string id, char * vertexFile) : Entity(id, vertexFile, false){}

void Tabuleiro::draw(){
	/*glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glStencilMask(0xFF);
	glDepthMask(GL_FALSE);
	glClear(GL_STENCIL_BUFFER_BIT);*/

	Entity::draw();
}


void Tabuleiro::update(){}