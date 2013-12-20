#include "Entity.h"
#include "Camera.h"


Entity::Entity(std::string id, bool reflection){
	std::string texture;
	
	_id = id;
	_height = _px = _py = _pz = 0.0;
	_reflection = reflection;

	_mesh = NULL;
	_texture = NULL;
}


void Entity::draw(){

	glm::mat4 modelMatrix = glm::translate(glm::mat4(), glm::vec3(_px, _py, _pz)) * glm::mat4_cast(_q) * _matrix;
	glm::mat3 normalMatrix = glm::inverseTranspose(glm::mat3(Camera::getInstance()->getView()*modelMatrix));
	glUniformMatrix4fv(ProgramShader::getInstance()->getId("ModelMatrix"), 1, GL_FALSE, &modelMatrix[0][0]);
	glUniformMatrix3fv(ProgramShader::getInstance()->getId("NormalMatrix"), 1, GL_FALSE, &normalMatrix[0][0]);
	
	if(_texture != NULL) {
		_texture->bind();	
		glUniform1f(ProgramShader::getInstance()->getId("withTexture"), 1.0f);
	}
	else glUniform1f(ProgramShader::getInstance()->getId("withTexture"), 0.0f);
	
	if(_mesh != NULL)
		_mesh->draw();
	
	if(_texture != NULL)
		_texture->unbind();

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

		if(_texture != NULL) {
			_texture->bind();	
			glUniform1f(ProgramShader::getInstance()->getId("withTexture"), 1.0f);
		}
		else glUniform1f(ProgramShader::getInstance()->getId("withTexture"), 0.0f);
		_mesh->draw();
	
		if(_texture != NULL)
			_texture->unbind();

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
	if(_mesh != NULL)
		_mesh->~Mesh();
	if(_texture != NULL)
		_texture->~Texture();
}


std::string Entity::getId(){
	return _id;
}


void Entity::setMesh(char * filename, char * mtl){
	_mesh = new Mesh(filename, mtl);
}


void Entity::setTexture(char * filename){
	std::string texture;
	Utils::loadTexture(filename, texture);

	if(texture.size() > 0)
		_texture = new Texture(texture);
	else
		std::cout << "Texture " << filename << " does not exist." << std::endl;
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

void Entity::activateAnimation(){
	if(_texture != NULL)
		_texture->activateAnimation();
}


void Entity::desactivateAnimation(){
	if(_texture != NULL)
		_texture->desactivateAnimation();
}