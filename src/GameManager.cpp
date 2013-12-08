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


bool GameManager::isMouseOver(std::string id){
	if(id.compare("background") == 0 && _stencilValue == 0)
		return true;

	entityIterator e = _entities.find(id);
	if(e == _entities.end())
		return false;

	int stencil = std::distance(_entities.begin(), e)+1;
	if(stencil == _stencilValue)
		return true;
	return false;
}


void GameManager::init(){
	
	/**/
	Board * board = new Board("tabuleiro", "tabuleiro.xml");
	board->scale(1.8,1.8,0.1);
	board->translate(0,0,-0.05);
	add(board);
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

	glm::vec2 mouse = Input::getInstance()->getMousePostion();
	glm::vec2 m = Input::getInstance()->getMouseMotion();
	if(!Input::getInstance()->mouseWasPressed(GLUT_LEFT_BUTTON) && !Input::getInstance()->mouseWasPressed(GLUT_RIGHT_BUTTON))
		glReadPixels(mouse.x, glutGet(GLUT_WINDOW_HEIGHT) - mouse.y - 1, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &_stencilValue);

	glUseProgram(0);
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