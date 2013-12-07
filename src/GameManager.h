#pragma once

#include "Camera.h"
#include "Utils.h"
#include "ProgramShader.h"
#include "TangramPieces.h"
#include "Tabuleiro.h"
#include <iostream>
#include <map>



class GameManager {

	private:
		typedef std::map<const std::string, Entity *>::iterator entityIterator;
		std::map<const std::string, Entity *> _entities;
		GameManager();

	public:
		static GameManager * getInstance();
		void init();
		void add(Entity * entity);
		Entity * getEntityById(std::string id);
		std::string stencilToKey(int value);
		void destroyBufferObjects();
		void draw();
		void update();
};