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
	int window_height = glutGet(GLUT_WINDOW_HEIGHT);
	glReadPixels(x, window_height - y - 1, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &_stencilValue);

	_mouseButton = button;

	_lastMousePositionX = x;
	_lastMousePositionY = y;
}


void Input::mouseMotion(int x, int y) {
	float speed = 2.0;
	int window_height = glutGet(GLUT_WINDOW_HEIGHT);
	int window_width = glutGet(GLUT_WINDOW_WIDTH);

	float clipX = 1.0 / (window_width / speed);
	float clipY = - 1.0 / (window_height / speed);

	if(_stencilValue != GameManager::getInstance()->keyToInt("eixoX") &&
		_stencilValue != GameManager::getInstance()->keyToInt("eixoY") &&
		_stencilValue != GameManager::getInstance()->keyToInt("eixoZ"))
		Camera::getInstance()->rotate((y- _lastMousePositionY), (x - _lastMousePositionX));
	else if(_mouseButton == GLUT_LEFT_BUTTON) 
		GameManager::getInstance()->updatePiece(GameManager::getInstance()->intToKey(_stencilValue), "translation", (x - _lastMousePositionX)*clipX, (y- _lastMousePositionY)*clipY);
	else if(_mouseButton == GLUT_RIGHT_BUTTON) 
		GameManager::getInstance()->updatePiece(GameManager::getInstance()->intToKey(_stencilValue), "rotation", (x - _lastMousePositionX), (y- _lastMousePositionY));
	_lastMousePositionX = x;
	_lastMousePositionY = y;
}


void Input::mouseOver(int x, int y){
	int window_height = glutGet(GLUT_WINDOW_HEIGHT);
	glReadPixels(x, window_height - y - 1, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &_stencilValue);

	if(_stencilValue != GameManager::getInstance()->keyToInt("eixoX") &&
		_stencilValue != GameManager::getInstance()->keyToInt("eixoY") &&
		_stencilValue != GameManager::getInstance()->keyToInt("eixoZ")){

		if(_stencilValue != 0 && _stencilValue != GameManager::getInstance()->keyToInt("tabuleiro"))
			GameManager::getInstance()->selectPiece(GameManager::getInstance()->intToKey(_stencilValue));
		else 
			GameManager::getInstance()->clearSelection();
	}

	std::cout << _stencilValue << " " << GameManager::getInstance()->intToKey(_stencilValue) << std::endl;

}