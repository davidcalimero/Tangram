#pragma once

#include "GameManager.h"
#include "Camera.h"
#include <iostream>



class Input {

	private:
		int _lastMousePositionX;
		int _lastMousePositionY;
		GLuint _stencilValue;
		Input();
		int _mouseButton;

	public:
		static Input * getInstance();
		void keyHandler(unsigned char key, int x, int y);
		void mouse(int button, int state, int x, int y);
		void mouseMotion(int x, int y);
		void mouseOver(int x, int y);
		void mouseWheel(int wheel, int direction, int x, int y);
};