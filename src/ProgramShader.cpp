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
	glLinkProgram(_programId);
	_uniformModelMatrixId = glGetUniformLocation(_programId, "ModelMatrix");
	_uboId = glGetUniformBlockIndex(_programId, "SharedMatrices");
	glUniformBlockBinding(_programId, _uboId, 0);

	Utils::checkOpenGLError("ERROR: Could not create shaders.");
}


void ProgramShader::destroyShaderProgram()
{
	glUseProgram(0);
	glDetachShader(_programId, _vertexShaderId);
	glDetachShader(_programId, _fragmentShaderId);
	glDeleteShader(_vertexShaderId);
	glDeleteShader(_fragmentShaderId);
	glDeleteProgram(_programId);

	Utils::checkOpenGLError("ERROR: Could not destroy shaders.");
}


const GLuint ProgramShader::getProgramId() const{
	return _programId;
}


const GLuint ProgramShader::getVertexShaderId() const{
		return _vertexShaderId;
}


const GLuint ProgramShader::getFragmentShaderId() const{
		return _fragmentShaderId;
}


const GLint ProgramShader::getUniformModelMatrixId() const{
	return _uniformModelMatrixId;
}