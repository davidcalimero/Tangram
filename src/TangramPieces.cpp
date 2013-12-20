#include "TangramPieces.h"



TangramPieces::TangramPieces(std::string id) : Entity(id, true){}


void TangramPieces::setPos(float px, float py, float pz, glm::quat q){
	setRotation(q);
	setTranslation(px, py, pz);
}


void TangramPieces::resetPos(float x, float y, float z, glm::quat q) {
	setTranslation(x, y, z);
	setRotation(q);
}


void TangramPieces::update(){
	float speed = 3.25;
	int window_height = glutGet(GLUT_WINDOW_HEIGHT);
	int window_width = glutGet(GLUT_WINDOW_WIDTH);
	float clipX = 1.0 / (window_width / speed);
	float clipY = - 1.0 / (window_height / speed);
	glm::mat4 view = Camera::getInstance()->getView();
	glm::vec2 mouse = Input::getInstance()->getMouseMotion();

	if(GameManager::getInstance()->isMouseOver(_id)){

		if(Input::getInstance()->mouseWasPressed(GLUT_LEFT_BUTTON)){
			glm::mat4 t =  glm::inverse(view)* glm::translate(glm::vec3(mouse.x*clipX, mouse.y*clipY, 0)) * view;
			translate(t[3][0], t[3][1], t[3][2]);
		}

		else if(Input::getInstance()->mouseWasPressed(GLUT_RIGHT_BUTTON)){
			glm::mat4 tx =  glm::inverse(view)* glm::translate(glm::vec3(0, 1, 0)) * view;
			glm::vec3 vx(tx[3][0],tx[3][1],tx[3][2]);
			glm::normalize(vx);
			rotate(vx.x, vx.y, vx.z, mouse.x);

			glm::mat4 ty =  glm::inverse(view)* glm::translate(glm::vec3(1, 0, 0)) * view;
			glm::vec3 vy(ty[3][0],ty[3][1],ty[3][2]);
			glm::normalize(vy);
			rotate(vy.x, vy.y, vy.z, mouse.y);
		}
	}
}