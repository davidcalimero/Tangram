#include "Frame.h"

Frame::Frame(std::string id) : Entity(id, false){}

void Frame::update(){}

void Frame::updateShader(){
	glUniform1i(ProgramShader::getInstance()->getId("material"), 0);
}