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



void GameManager::init(){

	glm::quat qcoords;
	glm::vec3 pcoords;

	_program = ProgramShader::getInstance()->createShaderProgram("shaders/vertex.glsl", 
																 "shaders/fragment.glsl");

	_postProgram = ProgramShader::getInstance()->createShaderProgram("shaders/vertexPostProcessing.glsl", 
																	 "shaders/fragmentPostProcessing.glsl");

	glGenFramebuffers(1, &frameBufferPP);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferPP);
	glGenTextures(1, &texColorBufferPP);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texColorBufferPP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenRenderbuffers(1, &rboStencilDepthPP);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	_light = new Light(glm::vec3(0-2.0,-2.0,2.0), 
					   glm::vec3(0.5,0.5,0.5), 
					   glm::vec3(0.9,0.9,0.9), 
					   glm::vec3(0.9,0.9,0.9));
	
	_postProcessing = 0;

	quad = new Frame("plano", "mesh/quad.obj", "materials/quad.mtl");

	/**/
	Utils::loadScene("scene/currentScene.xml", "mesa", &qcoords, &pcoords);	
	Board * board = new Board("mesa", "mesh/cube.obj", "materials/mesa.mtl");	
	board->baseScale(2.2, 2.2, 0.0);
	board->borderScale(0.1, 2.1, 0.1);
	board->setTranslation(pcoords.x, pcoords.y, pcoords.z);	
	add(board);

	/**/
	Utils::loadScene("scene/currentScene.xml", "espelho", &qcoords, &pcoords);
	_mirror = new Mirror("espelho", "mesh/cube.obj", "materials/espelho.mtl");
	_mirror->scale(2.0, 2.0, 0.0001);
	_mirror->setTranslation(pcoords.x, pcoords.y, pcoords.z);

	/**/
	Utils::loadScene("scene/currentScene.xml", "trianguloVermelho", &qcoords, &pcoords);
	TangramPieces * trianguloVermelho = new TangramPieces("trianguloVermelho", "mesh/prism.obj", "materials/trianguloVermelho.mtl");
	trianguloVermelho->scale(sqrt(2.0)/2.0, sqrt(2.0)/2.0, 0.25);
	trianguloVermelho->setPos(pcoords.x, pcoords.y, pcoords.z, qcoords);
	add(trianguloVermelho);

	/**/
	Utils::loadScene("scene/currentScene.xml", "trianguloRoxo", &qcoords, &pcoords);
	TangramPieces * trianguloRoxo = new TangramPieces("trianguloRoxo", "mesh/prism.obj", "materials/trianguloRoxo.mtl");
	trianguloRoxo->scale(sqrt(2.0)/2.0, sqrt(2.0)/2.0, 0.23);
	trianguloRoxo->setPos(pcoords.x, pcoords.y, pcoords.z, qcoords);
	add(trianguloRoxo);

	/**/
	Utils::loadScene("scene/currentScene.xml", "trianguloAzul", &qcoords, &pcoords);
	TangramPieces * trianguloAzul = new TangramPieces("trianguloAzul", "mesh/prism.obj", "materials/trianguloAzul.mtl");
	trianguloAzul->scale(1.0/2.0, 1.0/2.0, 0.13);
	trianguloAzul->setPos(pcoords.x, pcoords.y, pcoords.z, qcoords);
	add(trianguloAzul);

	/**/
	Utils::loadScene("scene/currentScene.xml", "trianguloVerde", &qcoords, &pcoords);
	TangramPieces * trianguloVerde = new TangramPieces("trianguloVerde", "mesh/prism.obj", "materials/trianguloVerde.mtl");
	trianguloVerde->scale(sqrt(2.0)/4.0, sqrt(2.0)/4.0, 0.21);
	trianguloVerde->setPos(pcoords.x, pcoords.y, pcoords.z, qcoords);
	add(trianguloVerde);

	/**/
	Utils::loadScene("scene/currentScene.xml", "trianguloRosa", &qcoords, &pcoords);
	TangramPieces * trianguloRosa = new TangramPieces("trianguloRosa", "mesh/prism.obj", "materials/trianguloRosa.mtl");
	trianguloRosa->scale(sqrt(2.0)/4.0, sqrt(2.0)/4.0, 0.17);
	trianguloRosa->setPos(pcoords.x, pcoords.y, pcoords.z, qcoords);
	add(trianguloRosa);

	/**/
	Utils::loadScene("scene/currentScene.xml", "quadradoLaranja", &qcoords, &pcoords);
	TangramPieces * quadradoLaranja = new TangramPieces("quadradoLaranja", "mesh/cube.obj", "materials/quadradoLaranja.mtl");
	quadradoLaranja->scale(sqrt(2.0)/4.0, sqrt(2.0)/4.0, 0.19);
	quadradoLaranja->setPos(pcoords.x, pcoords.y, pcoords.z, qcoords);
	add(quadradoLaranja);

	/**/
	Utils::loadScene("scene/currentScene.xml", "quadradoAmarelo", &qcoords, &pcoords);
	TangramPieces * quadradoAmarelo = new TangramPieces("quadradoAmarelo", "mesh/cube.obj", "materials/quadradoAmarelo.mtl");
	quadradoAmarelo->scale(1.0/4.0, 1.0/2.0, 0.15);
	quadradoAmarelo->shear(0.0, 1.0);
	quadradoAmarelo->setPos(pcoords.x, pcoords.y, pcoords.z, qcoords);
	add(quadradoAmarelo);
	/**/
}


void GameManager::draw(){
	ProgramShader::getInstance()->bind(_program);
	Camera::getInstance()->put();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	if(_postProcessing){
		glBindFramebuffer(GL_FRAMEBUFFER, frameBufferPP);
		//Color Texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texColorBufferPP);
		int width = glutGet(GLUT_WINDOW_WIDTH);
		int height = glutGet(GLUT_WINDOW_HEIGHT);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBufferPP, 0);
		glBindRenderbuffer(GL_RENDERBUFFER, rboStencilDepthPP);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_STENCIL, width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rboStencilDepthPP);
		assert(glCheckFramebufferStatus(GL_FRAMEBUFFER));

		glClearColor(0.1,0.1,0.1,1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	_light->setShaderLightValues(false);

	// PIECES
	for (entityIterator i = _entities.begin(); i != _entities.end(); i++){
		glStencilFunc(GL_GREATER, std::distance(_entities.begin(), i)+2 , -1);
		i->second->draw();
	}

	// MIRROR
	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilMask(0xFF);
	glDepthMask(GL_FALSE);	
	_mirror->draw();
	glDepthMask(GL_TRUE);

	// REFLECTIONS
	_light->setShaderLightValues(true);
	glStencilFunc(GL_EQUAL, 1, 0xFF); 
	for (entityIterator i = _entities.begin(); i != _entities.end(); i++){
		i->second->drawReflection();
	}

	if(_postProcessing) {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClearColor(0.1,0.1,0.1,1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		ProgramShader::getInstance()->bind(_postProgram);
		glUniform1i(ProgramShader::getInstance()->getId("tex"), 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texColorBufferPP);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_STENCIL_TEST);
		quad->draw();
		glEnable(GL_STENCIL_TEST);
		glEnable(GL_DEPTH_TEST);
		glBindFramebuffer(GL_FRAMEBUFFER, frameBufferPP);
	}

	ProgramShader::getInstance()->unBind();
}

void GameManager::update(){

	glm::quat qcoords;
	glm::vec3 pcoords;

	// Camera and entities update
	Camera::getInstance()->update();
	for (entityIterator i = _entities.begin(); i != _entities.end(); i++)
		i->second->update();

	//Check if mouse over object
	for (entityIterator i = _entities.begin(); i != _entities.end(); i++){
		if(isMouseOver(i->first)){
			i->second->activateAnimation();
		}
		else
			i->second->desactivateAnimation();
	}

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

	int width = glutGet(GLUT_WINDOW_WIDTH);
	int height = glutGet(GLUT_WINDOW_HEIGHT);

	// Mouse Over
	glm::vec2 mp = Input::getInstance()->getMousePostion();
	if( !Input::getInstance()->mouseWasPressed(GLUT_LEFT_BUTTON) && 
		!Input::getInstance()->mouseWasPressed(GLUT_RIGHT_BUTTON))
		glReadPixels(mp.x, height - mp.y - 1, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &_stencilValue);

	std::cout << _stencilValue << std::endl;

	// Taking screenshot
	if(Input::getInstance()->keyWasReleased('M')) {
		std::string _filename = "screenshots/screenshot";
		Utils::screenshot(_filename, width, height);
	}

	// Apply postprocessing
	if(Input::getInstance()->keyWasReleased('E')) {
		_postProcessing = (_postProcessing+1)%2;
	}
}


void GameManager::destroyBufferObjects(){
	ProgramShader::getInstance()->destroyShaderProgram();
	for (entityIterator i = _entities.begin(); i != _entities.end(); i++)
		i->second->~Entity();
	Camera::getInstance()->~Camera();
	glDeleteFramebuffers(1, &frameBufferPP);
}