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

	glBindBuffer(GL_ARRAY_BUFFER, _vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, _normals.size() * sizeof(glm::vec3), &_normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(NORMALS);
	glVertexAttribPointer(NORMALS, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbo[3]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned short), &_indices[0] , GL_STATIC_DRAW);

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
	glDrawArrays(GL_TRIANGLES, 0, _vertices.size());
	//glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_BYTE, (GLvoid*)0);
}


Mesh::~Mesh(){
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