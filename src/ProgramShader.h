#pragma once

#include "Utils.h"

#include <iostream>



class ProgramShader {

	private:
		GLuint _vertexShaderId;
		GLuint _fragmentShaderId;
		GLuint _programId;
		int compileShader(char * shaderFile, int shaderType);
		ProgramShader();

	public:
		static ProgramShader * getInstance();
		void createShaderProgram(char * vSFile, char * fSFile);
		void destroyShaderProgram();
		const GLuint getUId(std::string key) const;
		const GLint getId(std::string key) const;
};