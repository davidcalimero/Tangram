#pragma once

#include "Camera.h"
#include "Utils.h"
#include "ProgramShader.h"
#include "TangramPieces.h"
#include "Board.h"
#include <iostream>
#include <map>



class GameManager {

	private:
		typedef std::map<const std::string, Entity *>::iterator entityIterator;
		std::map<const std::string, Entity *> _entities;
		GLuint _stencilValue;
		GameManager();

	public:
		static GameManager * getInstance();
		void init();
		void add(Entity * entity);
		Entity * getEntityById(std::string id);
		bool isMouseOver(std::string id);
		void destroyBufferObjects();
		void draw();
		void update();
};