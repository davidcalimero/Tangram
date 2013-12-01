#include "GameManager.h"



GameManager::GameManager(){}


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
	entityIterator i = _entities.begin();
	for(int j = 0; j < key-1; i++, j++);
	return i->first;
}


void GameManager::update(){
	for (entityIterator i = _entities.begin(); i != _entities.end(); i++){
		i->second->update();
	}
}


void GameManager::movePiece(std::string key){
	((TangramPieces*)_entities.find(key)->second)->swapPos();
}


void GameManager::destroyBufferObjects(){
	for (entityIterator i = _entities.begin(); i != _entities.end(); i++){
		i->second->~Entity();
	}
}