#pragma once

#include "Camera.h"
#include "TangramPieces.h"
#include "Board.h"
#include "Light.h"

#include <iostream>
#include <map>



class GameManager {

	private:
		typedef std::map<const std::string, Entity *>::iterator entityIterator;
		std::map<const std::string, Entity *> _entities;
		GLuint _stencilValue;
		GameManager();
		Light * _light;

	public:
		static GameManager * getInstance();
		void init();
		void add(Entity * entity);
		Entity * getEntityById(std::string id);
		bool isMouseOver(std::string id);
		void destroyBufferObjects();
		void draw();
		void update();
		void postProcessing();
};