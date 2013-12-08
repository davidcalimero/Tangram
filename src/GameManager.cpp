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

	glm::quat qcoords;
	glm::vec3 pcoords;
	
	/**/
	Utils::sceneParser("sceneTest.xml", "tabuleiro", &qcoords, &pcoords);
	Board * board = new Board("tabuleiro", "tabuleiro.xml");
	board->scale(1.8, 1.8, 0.1);
	board->translate(pcoords.x, pcoords.y, pcoords.z);
	add(board);

	/**/
	Utils::sceneParser("sceneTest.xml", "trianguloVermelho", &qcoords, &pcoords);
	TangramPieces * trianguloVermelho = new TangramPieces("trianguloVermelho", "trianguloVermelho.xml");
	trianguloVermelho->scale(sqrt(2.0)/2.0, sqrt(2.0)/2.0, 0.25);
	trianguloVermelho->setPos(pcoords.x, pcoords.y, pcoords.z, qcoords);
	add(trianguloVermelho);

	/**/
	Utils::sceneParser("sceneTest.xml", "trianguloRoxo", &qcoords, &pcoords);
	TangramPieces * trianguloRoxo = new TangramPieces("trianguloRoxo", "trianguloRoxo.xml");
	trianguloRoxo->scale(sqrt(2.0)/2.0, sqrt(2.0)/2.0, 0.23);
	trianguloRoxo->setPos(pcoords.x, pcoords.y, pcoords.z, qcoords);
	add(trianguloRoxo);

	/**/
	Utils::sceneParser("sceneTest.xml", "trianguloAzul", &qcoords, &pcoords);
	TangramPieces * trianguloAzul = new TangramPieces("trianguloAzul", "trianguloAzul.xml");
	trianguloAzul->scale(1.0/2.0, 1.0/2.0, 0.13);
	trianguloAzul->setPos(pcoords.x, pcoords.y, pcoords.z, qcoords);
	add(trianguloAzul);

	/**/
	Utils::sceneParser("sceneTest.xml", "trianguloVerde", &qcoords, &pcoords);
	TangramPieces * trianguloVerde = new TangramPieces("trianguloVerde", "trianguloVerde.xml");
	trianguloVerde->scale(sqrt(2.0)/4.0, sqrt(2.0)/4.0, 0.21);
	trianguloVerde->setPos(pcoords.x, pcoords.y, pcoords.z, qcoords);
	add(trianguloVerde);

	/**/
	Utils::sceneParser("sceneTest.xml", "trianguloRosa", &qcoords, &pcoords);
	TangramPieces * trianguloRosa = new TangramPieces("trianguloRosa", "trianguloRosa.xml");
	trianguloRosa->scale(sqrt(2.0)/4.0, sqrt(2.0)/4.0, 0.17);
	trianguloRosa->setPos(pcoords.x, pcoords.y, pcoords.z, qcoords);
	add(trianguloRosa);

	/**/
	Utils::sceneParser("sceneTest.xml", "quadradoLaranja", &qcoords, &pcoords);
	TangramPieces * quadradoLaranja = new TangramPieces("quadradoLaranja", "quadradoLaranja.xml");
	quadradoLaranja->scale(sqrt(2.0)/4.0, sqrt(2.0)/4.0, 0.19);
	quadradoLaranja->setPos(pcoords.x, pcoords.y, pcoords.z, qcoords);
	add(quadradoLaranja);

	/**/
	Utils::sceneParser("sceneTest.xml", "quadradoAmarelo", &qcoords, &pcoords);
	TangramPieces * quadradoAmarelo = new TangramPieces("quadradoAmarelo", "quadradoAmarelo.xml");
	quadradoAmarelo->scale(1.0/4.0, 1.0/2.0, 0.15);
	quadradoAmarelo->shear(0.0, 1.0);
	quadradoAmarelo->setPos(pcoords.x, pcoords.y, pcoords.z, qcoords);
	add(quadradoAmarelo);

	/**/
}


void GameManager::draw(){
	glUseProgram(ProgramShader::getInstance()->getUId("Program"));

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