#pragma once

#include "Entity.h"
#include "Utils.h"
#include "ProgramShader.h"
#include "TangramPieces.h"
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
		void destroyBufferObjects();
		void draw();
		int keyToInt(std::string key);
		std::string intToKey(int key);
		void update();
		void movePiece(std::string key);
};