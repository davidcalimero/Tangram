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

	_light = new Light(glm::vec3(0-2.0,-2.0,2.0), glm::vec3(0.5,0.5,0.5), glm::vec3(0.9,0.9,0.9), glm::vec3(0.9,0.9,0.9));
	
	/**/
	Utils::loadScene("currentScene.xml", "tabuleiro", &qcoords, &pcoords);
	Board * board = new Board("tabuleiro", "cube.obj");
	board->getMesh()->setValues(glm::vec3(0.47,0.30,0.14),glm::vec3(0.8,0.52,0.24),glm::vec3(0.8,0.52,0.24),10);
	board->scale(1.8, 1.8, 0.1);
	board->translate(pcoords.x, pcoords.y, pcoords.z);
	add(board);

	/**/
	Utils::loadScene("currentScene.xml", "trianguloVermelho", &qcoords, &pcoords);
	TangramPieces * trianguloVermelho = new TangramPieces("trianguloVermelho", "prism.obj");
	trianguloVermelho->getMesh()->setValues(glm::vec3(0.59,0.17,0.17),glm::vec3(1.0,0.3,0.3),glm::vec3(1.0,0.3,0.3),10);
	trianguloVermelho->scale(sqrt(2.0)/2.0, sqrt(2.0)/2.0, 0.25);
	trianguloVermelho->setPos(pcoords.x, pcoords.y, pcoords.z, qcoords);
	add(trianguloVermelho);

	/**/
	Utils::loadScene("currentScene.xml", "trianguloRoxo", &qcoords, &pcoords);
	TangramPieces * trianguloRoxo = new TangramPieces("trianguloRoxo", "prism.obj");
	trianguloRoxo->getMesh()->setValues(glm::vec3(0.19,0.02,0.19),glm::vec3(0.5,0.2,0.5),glm::vec3(0.5,0.2,0.5),10);
	trianguloRoxo->scale(sqrt(2.0)/2.0, sqrt(2.0)/2.0, 0.23);
	trianguloRoxo->setPos(pcoords.x, pcoords.y, pcoords.z, qcoords);
	add(trianguloRoxo);

	/**/
	Utils::loadScene("currentScene.xml", "trianguloAzul", &qcoords, &pcoords);
	TangramPieces * trianguloAzul = new TangramPieces("trianguloAzul", "prism.obj");
	trianguloAzul->getMesh()->setValues(glm::vec3(0.09,0.33,0.45),glm::vec3(0.2,0.6,0.8),glm::vec3(0.2,0.6,0.8),10);
	trianguloAzul->scale(1.0/2.0, 1.0/2.0, 0.13);
	trianguloAzul->setPos(pcoords.x, pcoords.y, pcoords.z, qcoords);
	add(trianguloAzul);

	/**/
	Utils::loadScene("currentScene.xml", "trianguloVerde", &qcoords, &pcoords);
	TangramPieces * trianguloVerde = new TangramPieces("trianguloVerde", "prism.obj");
	trianguloVerde->getMesh()->setValues(glm::vec3(0.09,0.39,0.09),glm::vec3(0.2,0.7,0.2),glm::vec3(0.2,0.7,0.2),10);
	trianguloVerde->scale(sqrt(2.0)/4.0, sqrt(2.0)/4.0, 0.21);
	trianguloVerde->setPos(pcoords.x, pcoords.y, pcoords.z, qcoords);
	add(trianguloVerde);

	/**/
	Utils::loadScene("currentScene.xml", "trianguloRosa", &qcoords, &pcoords);
	TangramPieces * trianguloRosa = new TangramPieces("trianguloRosa", "prism.obj");
	trianguloRosa->getMesh()->setValues(glm::vec3(0.67,0.50,0.55),glm::vec3(1.0,0.7,0.8),glm::vec3(1.0,0.7,0.8),10);
	trianguloRosa->scale(sqrt(2.0)/4.0, sqrt(2.0)/4.0, 0.17);
	trianguloRosa->setPos(pcoords.x, pcoords.y, pcoords.z, qcoords);
	add(trianguloRosa);

	/**/
	Utils::loadScene("currentScene.xml", "quadradoLaranja", &qcoords, &pcoords);
	TangramPieces * quadradoLaranja = new TangramPieces("quadradoLaranja", "cube.obj");
	quadradoLaranja->getMesh()->setValues(glm::vec3(0.61,0.32,0.02),glm::vec3(1.0,0.5,0.0),glm::vec3(1.0,0.5,0.0),10);
	quadradoLaranja->scale(sqrt(2.0)/4.0, sqrt(2.0)/4.0, 0.19);
	quadradoLaranja->setPos(pcoords.x, pcoords.y, pcoords.z, qcoords);
	add(quadradoLaranja);

	/**/
	Utils::loadScene("currentScene.xml", "quadradoAmarelo", &qcoords, &pcoords);
	TangramPieces * quadradoAmarelo = new TangramPieces("quadradoAmarelo", "cube.obj");
	quadradoAmarelo->getMesh()->setValues(glm::vec3(0.63,0.63,0.10),glm::vec3(0.9,0.9,0.0),glm::vec3(0.9,0.9,0.0),10);
	quadradoAmarelo->scale(1.0/4.0, 1.0/2.0, 0.15);
	quadradoAmarelo->shear(0.0, 1.0);
	quadradoAmarelo->setPos(pcoords.x, pcoords.y, pcoords.z, qcoords);
	add(quadradoAmarelo);

	/**/
}


void GameManager::draw(){
	glUseProgram(ProgramShader::getInstance()->getUId("Program"));
	Camera::getInstance()->put();
	_light->setShaderLightValues();

	for (entityIterator i = _entities.begin(); i != _entities.end(); i++){
			glStencilFunc(GL_ALWAYS, std::distance(_entities.begin(), i)+1 , -1);
			i->second->draw();
	}

	glm::vec2 mp = Input::getInstance()->getMousePostion();
	if(!Input::getInstance()->mouseWasPressed(GLUT_LEFT_BUTTON) && !Input::getInstance()->mouseWasPressed(GLUT_RIGHT_BUTTON))
		glReadPixels(mp.x, glutGet(GLUT_WINDOW_HEIGHT) - mp.y - 1, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &_stencilValue);

	glUseProgram(0);
}


void GameManager::update(){

	glm::quat qcoords;
	glm::vec3 pcoords;

	// Camera and entities update
	Camera::getInstance()->update();
	for (entityIterator i = _entities.begin(); i != _entities.end(); i++)
		i->second->update();

	// Scene saving
	if(Input::getInstance()->keyWasReleased('G')) {
		for (entityIterator i = _entities.begin(); i != _entities.end(); i++) {
			if(i->second->getId().compare("tabuleiro") != 0)
				Utils::saveScene("currentScene.xml", i->second->getId(), i->second->getQuat(), i->second->getPos());
		}
	}

	// Scene reseting
	if(Input::getInstance()->keyWasReleased('R')) {
		for (entityIterator i = _entities.begin(); i != _entities.end(); i++) {
			if(i->second->getId().compare("tabuleiro") != 0) {
				Utils::loadScene("initialScene.xml", i->second->getId(), &qcoords, &pcoords);			
				i->second->resetPos(pcoords.x, pcoords.y, pcoords.z, qcoords);
			}
		}
	}

	// Taking screenshot
	if(Input::getInstance()->keyWasReleased('M')) {
		std::string _filename = "screenshot";
		int _width = glutGet(GLUT_WINDOW_WIDTH);
		int _height = glutGet(GLUT_WINDOW_HEIGHT);
		int state = Utils::screenshot(_filename, _width, _height);
		if (!state) std::cout << "Error: Cannot save the screenshot" << std::endl;
	}
}


void GameManager::destroyBufferObjects(){
	ProgramShader::getInstance()->destroyShaderProgram();
	for (entityIterator i = _entities.begin(); i != _entities.end(); i++)
		i->second->~Entity();
	Camera::getInstance()->~Camera();
}