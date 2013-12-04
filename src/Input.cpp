#include "Input.h"



Input::Input(){}


Input * Input::getInstance(){
	static Input instance;
	return &instance;
}


void Input::keyHandler(unsigned char key, int x, int y){
	switch(key){
		case 'P':
			Camera::getInstance()->change();
			break;
		case 'W':
			Camera::getInstance()->rotate(-1, 0);
			break;
		case 'S':
			Camera::getInstance()->rotate(1, 0);
			break;
		case 'A':
			Camera::getInstance()->rotate(0, -1);
			break;
		case 'D':
			Camera::getInstance()->rotate(0, 1);
			break;
	}
}


void Input::mouse(int button, int state, int x, int y) {
	_mouseButton = button;
	_lastMousePositionX = x;
	_lastMousePositionY = y;
}


void Input::mouseMotion(int x, int y) {
	if(_mouseButton == GLUT_LEFT_BUTTON){

		if(_stencilValue != 0 && _stencilValue != GameManager::getInstance()->keyToInt("tabuleiro"))
			GameManager::getInstance()->updatePiece(GameManager::getInstance()->intToKey(_stencilValue),"translation",(x - _lastMousePositionX),(y - _lastMousePositionY));
		else 
			Camera::getInstance()->rotate((y- _lastMousePositionY), (x - _lastMousePositionX));
	}
	
	else if(_mouseButton == GLUT_RIGHT_BUTTON){
		if(_stencilValue != 0 && _stencilValue != GameManager::getInstance()->keyToInt("tabuleiro"))
			GameManager::getInstance()->updatePiece(GameManager::getInstance()->intToKey(_stencilValue),"rotation",(x - _lastMousePositionX),(y - _lastMousePositionY));
	}

	_lastMousePositionX = x;
	_lastMousePositionY = y;
	
}


void Input::mouseOver(int x, int y){
	glReadPixels(x, glutGet(GLUT_WINDOW_HEIGHT) - y - 1, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &_stencilValue);
	GameManager::getInstance()->selectPiece(GameManager::getInstance()->intToKey(_stencilValue));
}


void Input::mouseWheel(int wheel, int direction, int x, int y){
	Camera::getInstance()->addToDistance(direction);
}