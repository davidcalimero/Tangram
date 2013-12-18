#include "Mesh.h"




Mesh::Mesh(char * objFile){
	Utils::loadObj(objFile, _indices, _vertices, _uvs, _normals);

	glGenVertexArrays(1, &_vaoId);
	glBindVertexArray(_vaoId);

	glGenBuffers(4, _vbo);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(glm::vec3), &_vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(VERTICES);
	glVertexAttribPointer(VERTICES, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, _uvs.size() * sizeof(glm::vec2), &_uvs[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(UVS);
	glVertexAttribPointer(UVS, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// BEGIN TEXTURES
	glGenTextures(1, &_tex);

	glBindTexture(GL_TEXTURE_2D, _tex);
	int width, height;
	unsigned char* image = SOIL_load_image("textures/wood.bmp", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	float color[] = {0.0, 0.0, 0.0, 1.0};
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// END TEXTURES

	glBindBuffer(GL_ARRAY_BUFFER, _vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, _normals.size() * sizeof(glm::vec3), &_normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(NORMALS);
	glVertexAttribPointer(NORMALS, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbo[3]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned short), &_indices[0] , GL_STATIC_DRAW);
	
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(VERTICES);
	glDisableVertexAttribArray(UVS);
	glDisableVertexAttribArray(NORMALS);

	Utils::checkOpenGLError("ERROR: Could not create VAOs and VBOs.");
}


void Mesh::draw(){
	glBindVertexArray(_vaoId);
	glBindTexture(GL_TEXTURE_2D, _tex);
	// Get IDs
	GLint ambientId = ProgramShader::getInstance()->getId("MaterialAmbient");
	GLint diffuseId = ProgramShader::getInstance()->getId("MaterialDiffuse");
	GLint specularId = ProgramShader::getInstance()->getId("MaterialSpecular");
	GLint shininessId = ProgramShader::getInstance()->getId("MaterialShininess");

	// Set Values
	glUniform1f(shininessId, _shininess);
	glUniform3fv(ambientId, 1, glm::value_ptr(_ambientColor));
	glUniform3fv(diffuseId, 1, glm::value_ptr(_diffuseColor));
	glUniform3fv(specularId, 1, glm::value_ptr(_specularColor));

	glDrawArrays(GL_TRIANGLES, 0, _vertices.size());
	glBindTexture(GL_TEXTURE_2D, 0);
	//glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_BYTE, (GLvoid*)0);
}


Mesh::~Mesh(){
	glDeleteTextures(1, &_tex);

	glDisableVertexAttribArray(VERTICES);
	glDisableVertexAttribArray(UVS);
	glDisableVertexAttribArray(NORMALS);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glDeleteBuffers(4, _vbo);
	glDeleteVertexArrays(1, &_vaoId);

	Utils::checkOpenGLError("ERROR: Could not destroy VAOs and VBOs.");
}


void Mesh::setValues(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess){
	_ambientColor = ambient;
	_diffuseColor = diffuse;
	_specularColor = specular;
	_shininess = shininess;
}