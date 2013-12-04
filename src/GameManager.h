#pragma once

#include "Entity.h"
#include "Camera.h"
#include "Utils.h"
#include "ProgramShader.h"
#include "TangramPieces.h"
#include "Axis.h"
#include <iostream>
#include <map>
#include <cmath>
#include <vector>



class GameManager {

	private:
		typedef std::map<const std::string, Entity *>::iterator entityIterator;
		std::map<const std::string, Entity *> _entities;
		Entity * _selected;
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
		void updatePiece(std::string axis, std::string transformation, float x, float y);
		//void movePiece(std::string key);
		void selectPiece(std::string key);
		void clearSelection();
};