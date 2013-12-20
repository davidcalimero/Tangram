#pragma once

#include "Camera.h"
#include "TangramPieces.h"
#include "Board.h"
#include "Mirror.h"
#include "Quad.h"
#include "Light.h"

#include <iostream>
#include <map>



class GameManager {

	private:
		typedef std::map<const std::string, Entity *>::iterator entityIterator;
		std::map<const std::string, Entity *> _entities;
		GameManager();
		Light * _light;
		Quad * _quad;
		Mirror * _mirror;
		Entity * _selected;
		GLuint frameBufferPP;
		GLuint texColorBufferNoise;
		GLuint _program;
		GLuint _postProgram;

		bool _greyscale, _noise, _vignette;
		float animationTryOut;


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