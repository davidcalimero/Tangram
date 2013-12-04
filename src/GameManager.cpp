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

	TangramPieces * tabuleiro = new TangramPieces("tabuleiro", "tabuleiro.xml");
	tabuleiro->scale(1.8,1.8,0.1);
	tabuleiro->setPos1(-0.9,-0.9,-0.1,0.0);
	tabuleiro->setPos2(-0.9,-0.9,-0.1,0.0);
	add(tabuleiro);

	TangramPieces * trianguloVermelho = new TangramPieces("trianguloVermelho", "trianguloVermelho.xml");
	trianguloVermelho->scale(sqrt(2.0)/2.0,sqrt(2.0)/2.0,0.25);
	trianguloVermelho->setPos1(0.0,0.0,0.0,45.0);
	trianguloVermelho->setPos2(-0.25,0.15,1.25,-135.0);
	add(trianguloVermelho);

	TangramPieces * trianguloRoxo = new TangramPieces("trianguloRoxo", "trianguloRoxo.xml");
	trianguloRoxo->scale(sqrt(2.0)/2.0,sqrt(2.0)/2.0,0.23);
	trianguloRoxo->setPos1(0.0,0.0,0.0,135.0);
	trianguloRoxo->setPos2(0.25,0.05,0.25,45.0);
	add(trianguloRoxo);

	TangramPieces * trianguloAzul = new TangramPieces("trianguloAzul", "trianguloAzul.xml");
	trianguloAzul->scale(1.0/2.0,1.0/2.0,0.13);
	trianguloAzul->setPos1(0.5,-0.5,0.0,90.0);
	trianguloAzul->setPos2(-0.25,0.1,0.75,180.0);
	add(trianguloAzul);

	TangramPieces * trianguloVerde = new TangramPieces("trianguloVerde", "trianguloVerde.xml");
	trianguloVerde->scale(sqrt(2.0)/4.0,sqrt(2.0)/4.0,0.21);
	trianguloVerde->setPos1(-0.25,-0.25,0.0,-135.0);
	trianguloVerde->setPos2(0.25,0.05,1.25,-135.0);
	add(trianguloVerde);

	TangramPieces * trianguloRosa = new TangramPieces("trianguloRosa", "trianguloRosa.xml");
	trianguloRosa->scale(sqrt(2.0)/4.0,sqrt(2.0)/4.0,0.17);
	trianguloRosa->setPos1(0.0,0.0,0.0,-45.0);
	trianguloRosa->setPos2(0.0,0.05,0.5,135.0);
	add(trianguloRosa);

	TangramPieces * quadradoLaranja = new TangramPieces("quadradoLaranja", "quadradoLaranja.xml");
	quadradoLaranja->scale(sqrt(2.0)/4.0,sqrt(2.0)/4.0,0.19);
	quadradoLaranja->setPos1(0.0,0.0,0.0,-135.0);
	quadradoLaranja->setPos2(0.0,-0.05,0.5,-135.0);
	add(quadradoLaranja);

	TangramPieces * quadradoAmarelo = new TangramPieces("quadradoAmarelo", "quadradoAmarelo.xml");
	quadradoAmarelo->scale(1.0/4.0,1.0/2.0,0.15);
	quadradoAmarelo->shear(0.0,1.0);
	quadradoAmarelo->setPos1(0.25,-0.25,0.0,0.0);
	quadradoAmarelo->setPos2(0.75,0.1,0.75,90.0);
	add(quadradoAmarelo);

	Axis * eixoX = new Axis("eixoX", "eixoVermelho.xml");
	eixoX->scale(1.0/10.0, 1.0/10.0, 1.0/10.0);
	eixoX->setTranslateVector(glm::vec3(1.0,0.0,0.0));
	add(eixoX);

	Axis * eixoY = new Axis("eixoY", "eixoVerde.xml");
	eixoY->scale(1.0/10.0, 1.0/10.0, 1.0/10.0);
	eixoY->setTranslateVector(glm::vec3(0.0,1.0,0.0));
	add(eixoY);

	Axis * eixoZ = new Axis("eixoZ", "eixoAzul.xml");
	eixoZ->scale(1.0/10.0, 1.0/10.0, 1.0/10.0);
	eixoZ->setTranslateVector(glm::vec3(0.0,1.0,0.0));
	add(eixoZ);
}


void GameManager::draw(){
	glUseProgram(ProgramShader::getInstance()->getProgramId());
	for (entityIterator i = _entities.begin(); i != _entities.end(); i++){
		if(i->first.compare("eixoX") != 0 && i->first.compare("eixoY") != 0 && i->first.compare("eixoZ") != 0){
			glStencilFunc(GL_ALWAYS, std::distance(_entities.begin(), i)+1 , -1);
			i->second->draw();
		}
	}

	if(_selected != NULL){
		glClear(GL_DEPTH_BUFFER_BIT);
		Axis * x = (Axis*)_entities.find("eixoX")->second;
		Axis * y = (Axis*)_entities.find("eixoY")->second;
		Axis * z = (Axis*)_entities.find("eixoZ")->second;

		x->setPosition(_selected->getPos().x, _selected->getPos().y, _selected->getPos().z);
		glStencilFunc(GL_ALWAYS, std::distance(_entities.begin(), _entities.find("eixoX"))+1 , -1);
		x->draw();

		y->setPosition(_selected->getPos().x, _selected->getPos().y, _selected->getPos().z);
		glStencilFunc(GL_ALWAYS, std::distance(_entities.begin(), _entities.find("eixoY"))+1 , -1);
		y->draw();

		z->setPosition(_selected->getPos().x, _selected->getPos().y, _selected->getPos().z);
		glStencilFunc(GL_ALWAYS, std::distance(_entities.begin(), _entities.find("eixoZ"))+1 , -1);
		z->draw();			
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


void GameManager::updatePiece(std::string axis, std::string transformation, float x, float y) {
	/*glm::vec3 u, v, s, tx, ty;
	Camera::getInstance()->getCameraRef(s, v, u);
	
	tx = s * x;
	ty = u * y;	

	_entities.find(pieceId)->second->translate(x, 0, y);
	//_entities.find(pieceId)->second->translate(tx.x, tx.y, tx.z);*/

	if(transformation.compare("translation") == 0)
		if(_selected != NULL)
			if(_entities.find("eixoX")->first.compare(axis) == 0)
				_selected->translate((x+y)/2,0,0);
			else if(_entities.find("eixoY")->first.compare(axis) == 0)
				_selected->translate(0,(x+y)/2,0);
			else if(_entities.find("eixoZ")->first.compare(axis) == 0)
				_selected->translate(0,0,(x+y)/2);

	if(transformation.compare("rotation") == 0)
		if(_selected != NULL)
			if(_entities.find("eixoX")->first.compare(axis) == 0)
				_selected->rotate(1,0,0,(x+y)/2);
			else if(_entities.find("eixoY")->first.compare(axis) == 0)
				_selected->rotate(0,1,0,(x+y)/2);
			else if(_entities.find("eixoZ")->first.compare(axis) == 0)
				_selected->rotate(0,0,1,(x+y)/2);
}

/*
void GameManager::movePiece(std::string key){
	((TangramPieces*)_entities.find(key)->second)->swapPos();
}*/


void GameManager::destroyBufferObjects(){
	for (entityIterator i = _entities.begin(); i != _entities.end(); i++){
		i->second->~Entity();
	}
}


void GameManager::selectPiece(std::string key){
	_selected =  _entities.find(key)->second;
}


void GameManager::clearSelection(){
	_selected = NULL;
}