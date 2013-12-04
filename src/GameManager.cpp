#include "GameManager.h"



GameManager::GameManager(){
	_selected = NULL;
}


GameManager * GameManager::getInstance(){
	static GameManager instance;
	return &instance;
}


void GameManager::add(Entity * entity){
	_entities.insert(std::make_pair(entity->getId(), entity));
}


Entity * GameManager::getEntityById(std::string id){
	return _entities.find(id)->second;
}


void GameManager::init(){
	
	/**/
	TangramPieces * tabuleiro = new TangramPieces("tabuleiro", "tabuleiro.xml");
	tabuleiro->scale(1.8,1.8,0.1);
	tabuleiro->setPos(0,0,-0.05,0);
	add(tabuleiro);
	/**/
	TangramPieces * trianguloVermelho = new TangramPieces("trianguloVermelho", "trianguloVermelho.xml");
	trianguloVermelho->scale(sqrt(2.0)/2.0,sqrt(2.0)/2.0,0.25);
	trianguloVermelho->setPos(0.0,1/4.0,0.125,45.0);
	add(trianguloVermelho);
	/**/
	TangramPieces * trianguloRoxo = new TangramPieces("trianguloRoxo", "trianguloRoxo.xml");
	trianguloRoxo->scale(sqrt(2.0)/2.0,sqrt(2.0)/2.0,0.23);
	trianguloRoxo->setPos(-1/4.0,0,0.115,135.0);
	add(trianguloRoxo);
	/**/
	TangramPieces * trianguloAzul = new TangramPieces("trianguloAzul", "trianguloAzul.xml");
	trianguloAzul->scale(1.0/2.0,1.0/2.0,0.13);
	trianguloAzul->setPos(0.375,-0.375,0.065,90.0);
	add(trianguloAzul);
	/**/
	TangramPieces * trianguloVerde = new TangramPieces("trianguloVerde", "trianguloVerde.xml");
	trianguloVerde->scale(sqrt(2.0)/4.0,sqrt(2.0)/4.0,0.21);
	trianguloVerde->setPos(-0.25, -0.375,0.105,-135.0);
	add(trianguloVerde);
	/**/
	TangramPieces * trianguloRosa = new TangramPieces("trianguloRosa", "trianguloRosa.xml");
	trianguloRosa->scale(sqrt(2.0)/4.0,sqrt(2.0)/4.0,0.17);
	trianguloRosa->setPos(0.125,0.0,0.085,-45.0);
	add(trianguloRosa);
	/**/
	TangramPieces * quadradoLaranja = new TangramPieces("quadradoLaranja", "quadradoLaranja.xml");
	quadradoLaranja->scale(sqrt(2.0)/4.0,sqrt(2.0)/4.0,0.19);
	quadradoLaranja->setPos(0.0,-0.25,0.095,-135.0);
	add(quadradoLaranja);
	/**/
	TangramPieces * quadradoAmarelo = new TangramPieces("quadradoAmarelo", "quadradoAmarelo.xml");
	quadradoAmarelo->scale(1.0/4.0,1.0/2.0,0.15);
	quadradoAmarelo->shear(0.0,1.0);
	quadradoAmarelo->setPos(0.375,0.125,0.075,0.0);
	add(quadradoAmarelo);
	/**/
}


void GameManager::draw(){
	glUseProgram(ProgramShader::getInstance()->getProgramId());
	for (entityIterator i = _entities.begin(); i != _entities.end(); i++){
			glStencilFunc(GL_ALWAYS, std::distance(_entities.begin(), i)+1 , -1);
			i->second->draw();
	}
	glUseProgram(0);
}


int GameManager::keyToInt(std::string key){
	return std::distance(_entities.begin(), _entities.find(key))+1;
}


std::string GameManager::intToKey(int key){
	if(key == 0) return "background";
	entityIterator i = _entities.begin();
	for(int j = 0; j < key-1; i++, j++);
	return i->first;
}


void GameManager::update(){
	for (entityIterator i = _entities.begin(); i != _entities.end(); i++){
		i->second->update();
	}
}


void GameManager::updatePiece(std::string piece, std::string transformation, float x, float y) {
	float speed = 3.25;
	int window_height = glutGet(GLUT_WINDOW_HEIGHT);
	int window_width = glutGet(GLUT_WINDOW_WIDTH);
	float clipX = 1.0 / (window_width / speed);
	float clipY = - 1.0 / (window_height / speed);

	if(_selected != NULL){
		Entity *entity = GameManager::getInstance()->getEntityById(piece);
		glm::mat4 view = Camera::getInstance()->getView();

		if(transformation.compare("translation") == 0){
				glm::mat4 t =  glm::inverse(view)* glm::translate(glm::vec3(x*clipX, y*clipY, 0)) * view;
				entity->translate(t[3][0], t[3][1], t[3][2]);
		}

		else if(transformation.compare("rotation") == 0){
				glm::mat4 tx =  glm::inverse(view)* glm::translate(glm::vec3(0, 1, 0)) * view;
				glm::vec3 vx(tx[3][0],tx[3][1],tx[3][2]);
				glm::normalize(vx);
				entity->rotate(vx.x, vx.y, vx.z, x);

				glm::mat4 ty =  glm::inverse(view)* glm::translate(glm::vec3(1, 0, 0)) * view;
				glm::vec3 vy(ty[3][0],ty[3][1],ty[3][2]);
				glm::normalize(vy);
				entity->rotate(vy.x, vy.y, vy.z, y);
		}
	}
}


void GameManager::destroyBufferObjects(){
	for (entityIterator i = _entities.begin(); i != _entities.end(); i++){
		i->second->~Entity();
	}
}


void GameManager::selectPiece(std::string key){
	if(key.compare("tabuleiro") == 0 || key.compare("background") == 0)
		_selected = NULL;
	else
		_selected =  _entities.find(key)->second;
}