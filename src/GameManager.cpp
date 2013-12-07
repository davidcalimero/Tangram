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
	
	/**/
	Tabuleiro * tabuleiro = new Tabuleiro("tabuleiro", "tabuleiro.xml");
	tabuleiro->scale(1.8,1.8,0.1);
	tabuleiro->translate(0,0,-0.05);
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


std::string GameManager::stencilToKey(int value){
	if(value == 0) return "background";
	entityIterator i = _entities.begin();
	for(int j = 0; j < value-1; i++, j++);
	return i->first;

}


void GameManager::update(){
	Camera::getInstance()->update();
	for (entityIterator i = _entities.begin(); i != _entities.end(); i++){
		i->second->update();
	}
}


void GameManager::destroyBufferObjects(){
	ProgramShader::getInstance()->destroyShaderProgram();
	for (entityIterator i = _entities.begin(); i != _entities.end(); i++){
		i->second->~Entity();
	}
	Camera::getInstance()->~Camera();
}