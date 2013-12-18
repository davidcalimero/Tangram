#include "Mirror.h"

Mirror::Mirror(std::string id, char * vertexFile, char * mtlFile) : Entity(id, vertexFile, mtlFile, false){}

void Mirror::draw(){	

	Entity::draw();
	
}

void Mirror::update(){}