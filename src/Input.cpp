#include "Input.h"





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
	/* Need to check StencilBuffer */
	
	int window_height = glutGet(GLUT_WINDOW_HEIGHT);

	glReadPixels(x, window_height - y - 1, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &stencilValue);
	printf("Stencil Value: %u\n", stencilValue);
	if(stencilValue == 0){	//BackGround
		_lastMousePositionX = x;
		_lastMousePositionY = y;
	}
			
	//else Other Pieces - movê-las
	/**/
	
	

}




void Input::mouseMotion(int x, int y) 
{
	if(stencilValue == 0){
		Camera::getInstance()->rotate((y - _lastMousePositionY), (x - _lastMousePositionX));
		_lastMousePositionX = x;
		_lastMousePositionY = y;
	}
}