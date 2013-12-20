#include "Texture.h"

Texture::Texture(std::string textureName) {
	int width, height;

	_animationTryOut = 0.0f;
	_selected = false;
	_textureName = textureName;
	
	glGenTextures(1, &_textureID);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _textureID);
		
	std::string texpath = "textures/";
	texpath.append(_textureName);

	unsigned char* image = SOIL_load_image(texpath.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	float color[] = {0.0, 0.0, 0.0, 1.0};
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture(){
	glDeleteTextures(1, &_textureID);
}

void Texture::bind() {
	glBindTexture(GL_TEXTURE_2D, _textureID);
	if(_selected) _animationTryOut += 0.001;
	glUniform1f(ProgramShader::getInstance()->getId("animationTryOut"), _animationTryOut);
}

void Texture::unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1f(ProgramShader::getInstance()->getId("animationTryOut"), 0.0f);
}

void Texture::activateAnimation(){
	_selected = true;
}


void Texture::desactivateAnimation(){
	_selected = false;
	_animationTryOut = 0.0f;
}
