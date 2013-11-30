#include "Input.h"
#include "GameManager.h"
#include "Camera.h"




Input::Input(){}




Input * Input::getInstance(){
	static Input instance;
	return &instance;
}




void Input::keyHandler(unsigned char key, int x, int y){
	switch(key){
		case 'T':
			GameManager::getInstance()->movePiece();
			break;
		case 'P':
			Camera::getInstance()->change();
			break;
	}
}




void Input::mouse(int button, int state, int x, int y) 
{
	_lastMousePositionX = x;
	_lastMousePositionY = y;

}




void Input::mouseMotion(int x, int y) 
{
	Camera::getInstance()->rotate((y - _lastMousePositionY), (x - _lastMousePositionX));
	_lastMousePositionX = x;
	_lastMousePositionY = y;
}