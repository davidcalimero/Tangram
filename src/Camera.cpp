#include "Camera.h"



Camera::Camera(){
	_type = 1;
	_q = glm::rotate(glm::quat(),45, glm::vec3(0,0,1));
	glGenBuffers(1, &_vboUBId);
	glBindBuffer(GL_UNIFORM_BUFFER, _vboUBId);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(float)*32, 0, GL_STREAM_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, _vboUBId);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}


Camera::~Camera(){
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	glDeleteBuffers(1, &_vboUBId);
}


Camera * Camera::getInstance(){
	static Camera instance;
	return &instance;
}


void Camera::put(float racio){
	glm::mat4 projection;
	glm::mat4 view = glm::lookAt(glm::vec3(0.0,-4.0,2.0), glm::vec3(0.0,0.0,0.0), glm::vec3(0.0,0.0,1.0));
	if(_type){
		if (racio > 1)
			projection = glm::ortho(-1.5*racio, 1.5*racio, -1.5, 1.5, 1.0, 10.0);
		else 
			projection = glm::ortho(-1.5, 1.5, -1.5/racio, 1.5/racio, 1.0, 10.0);
	}
	else
		projection = glm::perspective(38.0f, racio, 1.0f, 10.0f);

	glBindBuffer(GL_UNIFORM_BUFFER, _vboUBId);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(float)*16, &(view*glm::mat4_cast(_q))[0][0]);
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(float)*16, sizeof(float)*16, &projection[0][0]);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}


void Camera::rotate(float angleX, float angleZ){
	_q = glm::rotate(glm::quat(),angleX, glm::vec3(1,0,0)) * glm::rotate(glm::quat(),angleZ, glm::vec3(0,0,1)) * _q;
}


void Camera::change(){
	_type = !_type;
}