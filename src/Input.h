#include "GameManager.h"
#include "Camera.h"
#include <iostream>

#pragma once

class Input {

	private:
		int _lastMousePositionX;
		int _lastMousePositionY;
		GLuint _stencilValue;
		Input();

	public:
		static Input * getInstance();
		void keyHandler(unsigned char key, int x, int y);
		void mouse(int button, int state, int x, int y);
		void mouseMotion(int x, int y);
};