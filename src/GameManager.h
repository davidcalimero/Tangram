#pragma once

#include "Entity.h"
#include <map>

class GameManager {

	private:
		typedef std::map<const std::string, Entity *>::iterator entityIterator;

		entityIterator piece;
		std::map<const std::string, Entity *> _entities;
		GameManager();

	public:
		static GameManager * getInstance();
		void init();
		void add(Entity * entity);
		Entity * getEntityById(std::string id);
		void destroyBufferObjects();
		void draw();
		void update();
		void movePiece();
};