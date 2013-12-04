#include "Camera.h"
#include <gtx/rotate_vector.hpp>



Camera::Camera(){
	_type = 1;

	_eye = glm::vec3(0.0,-4.0,0.0);
	_center = glm::vec3(0.0,0.0,0.0);
	_up = glm::vec3(0.0,0.0,1.0);
	_q = glm::angleAxis(90.0f, glm::vec3(1,0,0));
	 
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
	_view = glm::lookAt(_eye, _center, _up);

	if(_type){
		if (racio > 1)
			projection = glm::ortho(-1.5*racio, 1.5*racio, -1.5, 1.5, 1.0, 10.0);
		else 
			projection = glm::ortho(-1.5, 1.5, -1.5/racio, 1.5/racio, 1.0, 10.0);
	}
	else
		projection = glm::perspective(38.0f, racio, 1.0f, 10.0f);

	_view = _view*glm::mat4_cast(_q);

	glBindBuffer(GL_UNIFORM_BUFFER, _vboUBId);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(float)*16, &_view[0][0]);
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(float)*16, sizeof(float)*16, &projection[0][0]);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}


void Camera::rotate(int angleX, int angleZ){
	_q = glm::angleAxis((float)angleX, glm::vec3(1,0,0)) * glm::angleAxis((float)angleZ, glm::vec3(0,0,1)) * _q;
}


void Camera::change(){
	_type = !_type;
}

glm::vec3 Camera::getCameraAngles() {
	glm::vec3 angles = glm::eulerAngles(_q);
	return glm::vec3(angles.x, angles.y, angles.z);
}


glm::mat4 Camera::getView(){
	return _view;
}