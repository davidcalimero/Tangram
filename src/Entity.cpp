#include "Entity.h"
#include "Camera.h"


Entity::Entity(std::string id, char * objFile, char * mtlFile, bool reflection){
	_id = id;
	_height = _px = _py = _pz = 0.0;
	_reflection = reflection;

	_mesh = new Mesh(objFile, mtlFile);
}


void Entity::draw(){

	glm::mat4 modelMatrix = glm::translate(glm::mat4(), glm::vec3(_px, _py, _pz)) * glm::mat4_cast(_q) * _matrix;
	glm::mat3 normalMatrix = glm::inverseTranspose(glm::mat3(Camera::getInstance()->getView()*modelMatrix));
	glUniformMatrix4fv(ProgramShader::getInstance()->getId("ModelMatrix"), 1, GL_FALSE, &modelMatrix[0][0]);
	glUniformMatrix3fv(ProgramShader::getInstance()->getId("NormalMatrix"), 1, GL_FALSE, &normalMatrix[0][0]);
	
	_mesh->draw();

	Utils::checkOpenGLError("ERROR: Could not draw scene.");
}


void Entity::drawReflection(){

	if(_reflection){		
		
		glm::vec3 angles = glm::eulerAngles(_q);
		glm::quat rotation = glm::rotate(glm::quat(),angles.z,glm::vec3(0,0,1)) *
							 glm::rotate(glm::quat(),-angles.y,glm::vec3(0,1,0)) *
							 glm::rotate(glm::quat(),-angles.x,glm::vec3(1,0,0));
		glm::mat4 reflexModelMatrix = glm::translate(glm::mat4(), glm::vec3(_px, _py, -_pz)) *
									  glm::mat4_cast(rotation) *
									  glm::scale(glm::mat4(), glm::vec3(1, 1, -1)) *
									  _matrix;
		glm::mat3 reflexNormalMatrix = glm::inverseTranspose(glm::mat3(Camera::getInstance()->getView()*reflexModelMatrix));
		glUniformMatrix4fv(ProgramShader::getInstance()->getId("ModelMatrix"), 1, GL_FALSE, &reflexModelMatrix[0][0]);
		glUniformMatrix3fv(ProgramShader::getInstance()->getId("NormalMatrix"), 1, GL_FALSE, &reflexNormalMatrix[0][0]);

		glDisable(GL_CULL_FACE);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		_mesh->draw();
		glEnable(GL_CULL_FACE);	
	}

	Utils::checkOpenGLError("ERROR: Could not draw scene.");
}


glm::vec3 Entity::getPos(){
	return glm::vec3(_px, _py, _pz);
}

glm::quat Entity::getQuat() {
	return _q;
}


Entity::~Entity(){
	_mesh->~Mesh();
}


std::string Entity::getId(){
	return _id;
}


Mesh * Entity::getMesh(){
	return _mesh;
}


void Entity::setRotation(glm::quat q) {
	_q = q;
}

void Entity::setTranslation(float x, float y, float z) {
	_px = x;
	_py = y;
	_pz = z;
}


void Entity::rotate(float x, float y, float z, float angle){
	_q = glm::rotate(glm::quat(), angle, glm::vec3(x, y, z)) * _q;
}


void Entity::translate(float x, float y, float z){
	_px += x;
	_py += y;
	_pz = MAX(_pz + z, _height/2);
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