#include "Mirror.h"

Mirror::Mirror(std::string id) : Entity(id, false){}

void Mirror::draw(){
	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilMask(0xFF);
	glDepthMask(GL_FALSE);
	Entity::draw();
	glDepthMask(GL_TRUE);
	
}

void Mirror::update(){}


void Mirror::updateShader(){
	glUniform1i(ProgramShader::getInstance()->getId("material"), 2);
}