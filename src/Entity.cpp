#include "Entity.h"



Entity::Entity(std::string id, char * vertexFile, bool reflection){
	_id = id;
	_height = _px = _py = _pz = 0.0;
	_vertices = Utils::xmlParser(vertexFile, &_nVertices);
	_reflection = reflection;

	glGenVertexArrays(1, &_vaoId);
	glBindVertexArray(_vaoId);
	glGenBuffers(2, _vboId);
	glBindBuffer(GL_ARRAY_BUFFER, _vboId[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices[0])*_nVertices, _vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(VERTICES);
	glVertexAttribPointer(VERTICES, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glEnableVertexAttribArray(COLORS);
	glVertexAttribPointer(COLORS, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)sizeof(_vertices[0].XYZW));
	GLubyte * indices = Utils::index(_nVertices);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vboId[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices)*_nVertices, indices, GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(VERTICES);
	glDisableVertexAttribArray(COLORS);
	glBindVertexArray(0);

	Utils::checkOpenGLError("ERROR: Could not create VAOs and VBOs.");
}


void Entity::draw(){
	glBindVertexArray(_vaoId);

	//ORIGINAL PIECE
	glUniformMatrix4fv(ProgramShader::getInstance()->getUniformModelMatrixId(), 1, GL_FALSE, 
						&(glm::translate(glm::mat4(), 
							glm::vec3(_px, _py, _pz))*glm::mat4_cast(_q)*_matrix)[0][0]);
	glDrawElements(GL_TRIANGLES, _nVertices, GL_UNSIGNED_BYTE, (GLvoid*)0);


	//REFLECTED PIECE
	if(_reflection){
		/*glStencilFunc(GL_EQUAL, 1, 0xFF);
		glStencilMask(0x00);
		glDepthMask(GL_TRUE);*/

		glm::vec3 angles = glm::eulerAngles(_q);
		glm::quat rotation = glm::rotate(glm::quat(),-angles.x,glm::vec3(1,0,0));
		rotation = glm::rotate(glm::quat(),-angles.y,glm::vec3(0,1,0)) * rotation;
		rotation = glm::rotate(glm::quat(),angles.z,glm::vec3(0,0,1)) * rotation;

		glDisable(GL_CULL_FACE);
		glUniformMatrix4fv(ProgramShader::getInstance()->getUniformModelMatrixId(), 1, GL_FALSE,
							&( glm::translate(glm::mat4(), glm::vec3(_px, _py, -_pz))*
								glm::mat4_cast(rotation)*
								glm::scale(glm::mat4(), glm::vec3(1, 1, -1))*
								_matrix)[0][0]);

		glDrawElements(GL_TRIANGLES, _nVertices, GL_UNSIGNED_BYTE, (GLvoid*)0);
		glEnable(GL_CULL_FACE);
	}

	Utils::checkOpenGLError("ERROR: Could not draw scene.");
}


glm::vec3 Entity::getPos(){
	return glm::vec3(_px, _py, _pz);
}


Entity::~Entity(){
	glDisableVertexAttribArray(VERTICES);
	glDisableVertexAttribArray(COLORS);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glDeleteBuffers(2, _vboId);
	glDeleteVertexArrays(1, &_vaoId);

	Utils::checkOpenGLError("ERROR: Could not destroy VAOs and VBOs.");
}


std::string Entity::getId(){
	return _id;
}


void Entity::setRotation(glm::quat q) {
	_q = q;
	//std::cout << " quaternion: [ " << _q.x << " " << _q.y << " " << _q.z << " " << _q.w << " ]" << std::endl;
}


void Entity::rotate(float x, float y, float z, float angle){
	_q = glm::rotate(glm::quat(), angle, glm::vec3(x, y, z)) * _q;
}


void Entity::translate(float x, float y, float z){
	_px += x;
	_py += y;
	_pz += z;

	if(_id.compare("tabuleiro") != 0 && _pz < _height/2)
		_pz = _height/2;
}


void Entity::scale(float x, float y, float z){
	_matrix = glm::scale(glm::mat4(),glm::vec3(x,y,z))*_matrix;
	_height = z;
}


void Entity::shear(float x, float y){
	glm::mat4 shear = glm::mat4(1, y, 0, 0,
								x, 1, 0, 0,
								0, 0, 1, 0,
								0, 0, 0, 1);
	_matrix = shear*_matrix;
}


void Entity::lerp(float x, float y, float z, float k){
	float xf = ((_px - (_px * k)) + (x * k)) - _px;
	float yf = ((_py - (_py * k)) + (y * k)) - _py;
	float zf = ((_pz - (_pz * k)) + (z * k)) - _pz;
	translate(xf,yf,zf);
}