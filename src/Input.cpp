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
	}
}


void Input::mouse(int button, int state, int x, int y) {
	int window_height = glutGet(GLUT_WINDOW_HEIGHT);
	glReadPixels(x, window_height - y - 1, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &_stencilValue);

	if(_stencilValue == 0 || _stencilValue == GameManager::getInstance()->keyToInt("tabuleiro")){
		_lastMousePositionX = x;
		_lastMousePositionY = y;
	} 
	else if(state == GLUT_DOWN)
		GameManager::getInstance()->movePiece(GameManager::getInstance()->intToKey(_stencilValue));
}


void Input::mouseMotion(int x, int y) {
	if(_stencilValue == 0 || _stencilValue == GameManager::getInstance()->keyToInt("tabuleiro")){
		Camera::getInstance()->rotate((y - _lastMousePositionY), (x - _lastMousePositionX));
		_lastMousePositionX = x;
		_lastMousePositionY = y;
	}
}