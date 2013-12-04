#include "TangramPieces.h"

#define SWAP(T, a, b) {T temp = a; a = b; b = temp;}



TangramPieces::TangramPieces(std::string id, char * vertexFile) : Entity(id, vertexFile, true){}


void TangramPieces::setPos(float px, float py, float pz, float rz){
	rotate(0, 0, 1, rz);
	translate(px, py, pz);
}


void TangramPieces::update(){}