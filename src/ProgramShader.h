#pragma once

#include "GL/glew.h"
#include "GL/freeglut.h"

class ProgramShader {

	private:
		GLint _uniformModelMatrixId;
		GLint _uboId;
		GLuint _vertexShaderId;
		GLuint _fragmentShaderId;
		GLuint _programId;
		int compileShader(char * shaderFile, int shaderType);
		ProgramShader();

	public:
		static ProgramShader * getInstance();
		void createShaderProgram(char * vSFile, char * fSFile);
		void destroyShaderProgram();
		const GLuint getProgramId() const;
		const GLuint getVertexShaderId() const;
		const GLuint getFragmentShaderId() const;
		const GLint getUniformModelMatrixId() const;
};