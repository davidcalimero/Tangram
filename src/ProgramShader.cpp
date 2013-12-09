#include "ProgramShader.h"



ProgramShader::ProgramShader(){}


ProgramShader * ProgramShader::getInstance(){
	static ProgramShader instance;
	return &instance;
}


int ProgramShader::compileShader(char * shaderFile, int shaderType){
	const char* shader = Utils::readFile(shaderFile);
	int shaderId = glCreateShader(shaderType);
	glShaderSource(shaderId, 1, &shader, 0);
	glCompileShader(shaderId);
	return shaderId;
}


void ProgramShader::createShaderProgram(char * vSFile, char * fSFile){
	_vertexShaderId = compileShader(vSFile, GL_VERTEX_SHADER);
	_fragmentShaderId = compileShader(fSFile, GL_FRAGMENT_SHADER);
	_programId = glCreateProgram();
	glAttachShader(_programId, _vertexShaderId);
	glAttachShader(_programId, _fragmentShaderId);
	glBindAttribLocation(_programId, VERTICES, "in_Position");
	glBindAttribLocation(_programId, COLORS, "in_Color");
	glBindAttribLocation(_programId, NORMALS, "in_Normal");
	glLinkProgram(_programId);
	glUniformBlockBinding(_programId, glGetUniformBlockIndex(_programId, "SharedMatrices"), 0);

	Utils::checkOpenGLError("ERROR: Could not create shaders.");
}


void ProgramShader::destroyShaderProgram(){
	glUseProgram(0);
	glDetachShader(_programId, _vertexShaderId);
	glDetachShader(_programId, _fragmentShaderId);
	glDeleteShader(_vertexShaderId);
	glDeleteShader(_fragmentShaderId);
	glDeleteProgram(_programId);

	Utils::checkOpenGLError("ERROR: Could not destroy shaders.");
}


const GLuint ProgramShader::getUId(std::string key) const{
	if(key.compare("Program") == 0)
		return _programId;
	if(key.compare("VertexShader") == 0)
		return _vertexShaderId;
	if(key.compare("FragmentShader") == 0)
		return _fragmentShaderId;
}


const GLint ProgramShader::getId(std::string key) const{
	return glGetUniformLocation(_programId, key.c_str());
}