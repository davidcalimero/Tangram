#pragma once

#include "Camera.h"
#include "TangramPieces.h"
#include "Board.h"
#include "Mirror.h"
#include "Light.h"

#include <iostream>
#include <map>



class GameManager {

	private:
		typedef std::map<const std::string, Entity *>::iterator entityIterator;
		std::map<const std::string, Entity *> _entities;
		int _width, _height;
		GameManager();
		Light * _light;
		GLuint _stencilValue;
		GLuint frameBufferPP;
		GLuint texColorBufferPP;
		GLuint rboDepthStencilPP;
		GLuint depthrenderbufferPP;


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