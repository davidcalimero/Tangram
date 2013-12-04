#include "TangramPieces.h"

#define SWAP(T, a, b) {T temp = a; a = b; b = temp;}



TangramPieces::TangramPieces(std::string id, char * vertexFile) : Entity(id, vertexFile, true){}


void TangramPieces::setPos1(float px, float py, float pz, float rz){
	_px1 = px;
	_py1 = py;
	_pz1 = pz;
	_r1 = glm::rotate(glm::quat(), rz, glm::vec3(0, 0, 1));
	rotate(0, 0, 1, rz);
	translate(px, py, pz);
}


void TangramPieces::setPos2(float px, float py, float pz, float rz){
	_px2 = px;
	_py2 = py;
	_pz2 = pz;

	_r2 = glm::rotate(glm::quat(), 90, glm::vec3(1, 0, 0)) * glm::rotate(glm::quat(), rz, glm::vec3(0, 0, 1));
}


void TangramPieces::swapPos(){
	SWAP(float, _px1, _px2);
	SWAP(float, _py1, _py2);
	SWAP(float, _pz1, _pz2);
	SWAP(glm::quat, _r1, _r2);
}


void TangramPieces::update(){
	//float k = 0.01;

	//lerp rotate
	//slerp(_r1,k);
	//lerp translete
	//lerp(_px1, _py1, _pz1, k);
}