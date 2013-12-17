#include "Mirror.h"

Mirror::Mirror(std::string id, char * vertexFile) : Entity(id, vertexFile, false){}

void Mirror::draw(){	

	Entity::draw();
	
}

void Mirror::update(){}