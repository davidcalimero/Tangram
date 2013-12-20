#include "Frame.h"

Frame::Frame(std::string id) : Entity(id, false){}

void Frame::update(){}

void Frame::updateShader(){
	glUniform1i(ProgramShader::getInstance()->getId("material"), 0);
	glUniform1f(ProgramShader::getInstance()->getId("ringFrequency"), 6.72);
	glUniform1f(ProgramShader::getInstance()->getId("ringSharpness"),21.0);
	glUniform1f(ProgramShader::getInstance()->getId("ringScale"), 0.5);
	glUniform1f(ProgramShader::getInstance()->getId("noiseScale"), 1.0);
}