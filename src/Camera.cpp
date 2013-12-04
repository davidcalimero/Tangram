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
	glm::mat4 view = glm::lookAt(_eye, _center, _up);

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


void Camera::rotate(int angleX, int angleZ){
	_q = glm::angleAxis((float)angleX, glm::vec3(1,0,0)) * glm::angleAxis((float)angleZ, glm::vec3(0,0,1)) * _q;
}


void Camera::change(){
	_type = !_type;
}

/*
void Camera::getCameraRef(glm::vec3 & s, glm::vec3 & v, glm::vec3 & u) {
	glm::vec3 view, side;
	view = _center - _eye;
	v = glm::normalize(view);
	side = glm::cross(v, _up);
	s = glm::normalize(side);
	u = glm::cross(s, v);

	std::cout << "X: " << _angleX << " Z: " << _angleZ << std::endl;

	//glm::vec3 yz = glm::rotate(u ,-(float)_angleX, glm::vec3(1, 0, 0));
	//yz.y *= -1;

	//glm::vec3 xy = glm::rotate(u, (float)_angleZ, glm::vec3(0, 0, 1));

	u = _q*u;
	u.y = -u.y;
	u = glm::normalize(u);
	s = glm::cross(u, glm::rotate(u ,90.0f, glm::vec3(1, 0, 0)));

	//u = yz;
	//u.z *= -1;

	
	//u = glm::normalize(u);
	s = glm::normalize(s);

	std::cout << "u [ " <<u.x << " " << u.y << " " << u.z << " ]" << std::endl;
	std::cout << "s [ " << s.x << " " << s.y << " " << s.z << " ]" << std::endl;
}*/