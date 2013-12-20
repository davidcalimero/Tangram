#include "Quad.h"



Quad::Quad(std::string id) : Entity(id, false) {

}

void Quad::bind() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texColorBufferPP);
}


void Quad::init() {
	glGenTextures(1, &texColorBufferPP);
	bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenRenderbuffers(1, &rboStencilDepthPP);
}


void Quad::predraw() {
	int width = glutGet(GLUT_WINDOW_WIDTH);
	int height = glutGet(GLUT_WINDOW_HEIGHT);
	bind();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBufferPP, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, rboStencilDepthPP);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_STENCIL, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rboStencilDepthPP);
	assert(glCheckFramebufferStatus(GL_FRAMEBUFFER));

	glClearColor(0.1,0.1,0.1,1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void Quad::draw() {
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_STENCIL_TEST);
	bind();
	Entity::draw();
	glEnable(GL_STENCIL_TEST);
	glEnable(GL_DEPTH_TEST);
}

void Quad::update() {}


void Quad::updateShader(){
	glUniform1i(ProgramShader::getInstance()->getId("material"), -1);
}