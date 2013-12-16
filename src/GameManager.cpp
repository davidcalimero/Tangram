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

	if(id.compare("espelho") == 0 && _stencilValue == 1)
		return true;

	entityIterator e = _entities.find(id);
	if(e == _entities.end())
		return false;

	int stencil = std::distance(_entities.begin(), e)+2;
	if(stencil == _stencilValue)
		return true;
	return false;
}
Mirror * mirror;

void GameManager::init(){

	glm::quat qcoords;
	glm::vec3 pcoords;

	ProgramShader::getInstance()->createShaderProgram("shaders/vertex.glsl", "shaders/fragment.glsl");

	_light = new Light(glm::vec3(0-2.0,-2.0,2.0), glm::vec3(0.5,0.5,0.5), glm::vec3(0.9,0.9,0.9), glm::vec3(0.9,0.9,0.9));
	
	glGenFramebuffers(1, &frameBufferPP);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferPP);

	//Texture images
	glGenTextures(1, &texColorBufferPP);
	glBindTexture(GL_TEXTURE_2D, texColorBufferPP);
	_width = glutGet(GLUT_WINDOW_WIDTH);
	_height = glutGet(GLUT_WINDOW_HEIGHT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBufferPP, 0);

	//Checking if everything is allright!
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE){
		std::cout << "cenaz" << std::endl;
	}
	else std::cout << "Framebuffer cannot be used!" << std::endl;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);


		/**/
	Utils::loadScene("scene/currentScene.xml", "mesa", &qcoords, &pcoords);
	Board * board = new Board("mesa", "mesh/cube.obj");
	board->getMesh()->setValues(glm::vec3(0.47,0.30,0.14),glm::vec3(0.8,0.52,0.24),glm::vec3(0.8,0.52,0.24),10);
	board->scale(2.5, 2.5, 0.2);
	board->setTranslation(pcoords.x, pcoords.y, pcoords.z);
	add(board);


	/**/
	Utils::loadScene("scene/currentScene.xml", "espelho", &qcoords, &pcoords);
	mirror = new Mirror("espelho", "mesh/cube.obj");
	mirror->getMesh()->setValues(glm::vec3(0.1,0.1,0.1),glm::vec3(0.1,0.1,0.1),glm::vec3(0.1,0.1,0.1),10);
	mirror->scale(1.8, 1.8, 0.2);
	mirror->setTranslation(pcoords.x, pcoords.y, pcoords.z);
	//add(mirror);



	/**/
	Utils::loadScene("scene/currentScene.xml", "trianguloVermelho", &qcoords, &pcoords);
	TangramPieces * trianguloVermelho = new TangramPieces("trianguloVermelho", "mesh/prism.obj");
	trianguloVermelho->getMesh()->setValues(glm::vec3(0.59,0.17,0.17),glm::vec3(1.0,0.3,0.3),glm::vec3(1.0,0.3,0.3),10);
	trianguloVermelho->scale(sqrt(2.0)/2.0, sqrt(2.0)/2.0, 0.25);
	trianguloVermelho->setPos(pcoords.x, pcoords.y, pcoords.z, qcoords);
	add(trianguloVermelho);

	/**/
	Utils::loadScene("scene/currentScene.xml", "trianguloRoxo", &qcoords, &pcoords);
	TangramPieces * trianguloRoxo = new TangramPieces("trianguloRoxo", "mesh/prism.obj");
	trianguloRoxo->getMesh()->setValues(glm::vec3(0.19,0.02,0.19),glm::vec3(0.5,0.2,0.5),glm::vec3(0.5,0.2,0.5),10);
	trianguloRoxo->scale(sqrt(2.0)/2.0, sqrt(2.0)/2.0, 0.23);
	trianguloRoxo->setPos(pcoords.x, pcoords.y, pcoords.z, qcoords);
	add(trianguloRoxo);

	/**/
	Utils::loadScene("scene/currentScene.xml", "trianguloAzul", &qcoords, &pcoords);
	TangramPieces * trianguloAzul = new TangramPieces("trianguloAzul", "mesh/prism.obj");
	trianguloAzul->getMesh()->setValues(glm::vec3(0.09,0.33,0.45),glm::vec3(0.2,0.6,0.8),glm::vec3(0.2,0.6,0.8),10);
	trianguloAzul->scale(1.0/2.0, 1.0/2.0, 0.13);
	trianguloAzul->setPos(pcoords.x, pcoords.y, pcoords.z, qcoords);
	add(trianguloAzul);

	/**/
	Utils::loadScene("scene/currentScene.xml", "trianguloVerde", &qcoords, &pcoords);
	TangramPieces * trianguloVerde = new TangramPieces("trianguloVerde", "mesh/prism.obj");
	trianguloVerde->getMesh()->setValues(glm::vec3(0.09,0.39,0.09),glm::vec3(0.2,0.7,0.2),glm::vec3(0.2,0.7,0.2),10);
	trianguloVerde->scale(sqrt(2.0)/4.0, sqrt(2.0)/4.0, 0.21);
	trianguloVerde->setPos(pcoords.x, pcoords.y, pcoords.z, qcoords);
	add(trianguloVerde);

	/**/
	Utils::loadScene("scene/currentScene.xml", "trianguloRosa", &qcoords, &pcoords);
	TangramPieces * trianguloRosa = new TangramPieces("trianguloRosa", "mesh/prism.obj");
	trianguloRosa->getMesh()->setValues(glm::vec3(0.67,0.50,0.55),glm::vec3(1.0,0.7,0.8),glm::vec3(1.0,0.7,0.8),10);
	trianguloRosa->scale(sqrt(2.0)/4.0, sqrt(2.0)/4.0, 0.17);
	trianguloRosa->setPos(pcoords.x, pcoords.y, pcoords.z, qcoords);
	add(trianguloRosa);

	/**/
	Utils::loadScene("scene/currentScene.xml", "quadradoLaranja", &qcoords, &pcoords);
	TangramPieces * quadradoLaranja = new TangramPieces("quadradoLaranja", "mesh/cube.obj");
	quadradoLaranja->getMesh()->setValues(glm::vec3(0.61,0.32,0.02),glm::vec3(1.0,0.5,0.0),glm::vec3(1.0,0.5,0.0),10);
	quadradoLaranja->scale(sqrt(2.0)/4.0, sqrt(2.0)/4.0, 0.19);
	quadradoLaranja->setPos(pcoords.x, pcoords.y, pcoords.z, qcoords);
	add(quadradoLaranja);

	/**/
	Utils::loadScene("scene/currentScene.xml", "quadradoAmarelo", &qcoords, &pcoords);
	TangramPieces * quadradoAmarelo = new TangramPieces("quadradoAmarelo", "mesh/cube.obj");
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

	_light->setShaderLightValues(false);
	glStencilFunc(GL_GREATER, 1 , -1);
	mirror->draw();
	
	for (entityIterator i = _entities.begin(); i != _entities.end(); i++){
	//	if(i->first.compare("espelho") == 0)
			glStencilFunc(GL_GREATER, std::distance(_entities.begin(), i)+2 , -1);
	//	else if(i->first.compare("espelho") == 0)
	//		glStencilFunc(GL_GREATER, std::distance(_entities.begin(), i)+1 , 1);
	//	else
	//		glStencilFunc(GL_ALWAYS, std::distance(_entities.begin(), i)+1 , -1);
		i->second->draw();
	}
	_light->setShaderLightValues(true);
	for (entityIterator i = _entities.begin(); i != _entities.end(); i++){
			glStencilFunc(GL_ALWAYS, 0, -1);
			i->second->drawReflection();
	}
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
			if(i->second->getId().compare("mesa") != 0)
				Utils::saveScene("scene/currentScene.xml", i->second->getId(), i->second->getQuat(), i->second->getPos());
		}
		std::cout << "Saved in scene/currentScene.xml" << std::endl;
	}

	// Scene reseting
	if(Input::getInstance()->keyWasReleased('R')) {
		for (entityIterator i = _entities.begin(); i != _entities.end(); i++) {
			if(i->second->getId().compare("mesa") != 0) {
				Utils::loadScene("scene/initialScene.xml", i->second->getId(), &qcoords, &pcoords);			
				((TangramPieces *)i->second)->resetPos(pcoords.x, pcoords.y, pcoords.z, qcoords);
			}
		}
	}
}


void GameManager::postProcessing(){

	// Mouse Over
	glm::vec2 mp = Input::getInstance()->getMousePostion();
	if( !Input::getInstance()->mouseWasPressed(GLUT_LEFT_BUTTON) && 
		!Input::getInstance()->mouseWasPressed(GLUT_RIGHT_BUTTON))
		glReadPixels(mp.x, glutGet(GLUT_WINDOW_HEIGHT) - mp.y - 1, 1, 1, GL_STENCIL_INDEX, 
					 GL_UNSIGNED_INT, &_stencilValue);

	std::cout << _stencilValue << std::endl;

	// Taking screenshot
	if(Input::getInstance()->keyWasReleased('M')) {
		std::string _filename = "screenshots/screenshot";
		_width = glutGet(GLUT_WINDOW_WIDTH);
		_height = glutGet(GLUT_WINDOW_HEIGHT);
		int state = Utils::screenshot(_filename, _width, _height);
		if (!state) std::cout << "Error: Cannot save the screenshot" << std::endl;
	}

	if(Input::getInstance()->keyWasReleased('E')) {

		//verificar qual é o framebuffer que ta usado

		glBindFramebuffer(GL_FRAMEBUFFER, frameBufferPP);
		if(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE){
			std::cout << "Vai usar o framebuffer normal.... " << std::endl;
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
		else std::cout << "The effect could not be applied. Error in Framebuffer!" << std::endl;
	
	}
}


void GameManager::destroyBufferObjects(){
	ProgramShader::getInstance()->destroyShaderProgram();
	for (entityIterator i = _entities.begin(); i != _entities.end(); i++)
		i->second->~Entity();
	Camera::getInstance()->~Camera();
	glDeleteFramebuffers(1, &frameBufferPP);
}