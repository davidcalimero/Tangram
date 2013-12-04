#include "Axis.h"

Axis::Axis(std::string id, char * vertexFile) : Entity(id, vertexFile, false){}

glm::vec3 Axis::returnTranslateVector(){
	return _direction;
}

void Axis::setTranslateVector(glm::vec3 direction){
	_direction = direction;
}

void Axis::setPosition(float px, float py, float pz){
	_px = px;
	_py = py;
	_pz = pz;
}

void Axis::update(){

}