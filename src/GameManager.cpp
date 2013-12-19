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

	ProgramShader::getInstance()->createShaderProgram("shaders/vertex.glsl", 
													  "shaders/fragment.glsl");

	glGenFramebuffers(1, &frameBufferPP);
	glGenTextures(1, &texColorBufferPP);
	glGenRenderbuffers(1, &rboStencilDepthPP);

	_light = new Light(glm::vec3(0-2.0,-2.0,2.0), 
					   glm::vec3(0.5,0.5,0.5), 
					   glm::vec3(0.9,0.9,0.9), 
					   glm::vec3(0.9,0.9,0.9));
	
	/**/
	Utils::loadScene("scene/currentScene.xml", "espelho", &qcoords, &pcoords);
	mirror = new Mirror("espelho", "mesh/cube.obj", "materials/espelho.mtl");
	mirror->scale(2.2, 2.2, 0.05);
	mirror->setTranslation(pcoords.x, pcoords.y, pcoords.z);


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
	glUseProgram(ProgramShader::getInstance()->getUId("Program"));
	Camera::getInstance()->put();

	if(_postProcessing){
		//Texture images
		glBindFramebuffer(GL_FRAMEBUFFER, frameBufferPP);
		glBindTexture(GL_TEXTURE_2D, texColorBufferPP);
		_width = glutGet(GLUT_WINDOW_WIDTH);
		_height = glutGet(GLUT_WINDOW_HEIGHT);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBufferPP, 0);
		glBindRenderbuffer(GL_RENDERBUFFER, rboStencilDepthPP);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, _width, _height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rboStencilDepthPP);
		GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
		glDrawBuffers(1, DrawBuffers);
		//glBindFramebuffer(GL_FRAMEBUFFER, frameBufferPP);
		//glViewport(0,0,_width, _height);
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
	mirror->draw();
	glDepthMask(GL_TRUE);

	// REFLECTIONS
	_light->setShaderLightValues(true);
	glStencilFunc(GL_EQUAL, 1, 0xFF); 
	for (entityIterator i = _entities.begin(); i != _entities.end(); i++){
		i->second->drawReflection();
	}

	if(_postProcessing) {
		glUseProgram(0);
		ProgramShader::getInstance()->createShaderProgram("shaders/vertexPostProcessing.glsl", 
														  "shaders/fragmentPostProcessing.glsl");
		glBindFramebuffer(GL_FRAMEBUFFER, frameBufferPP);
		if(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE){
			std::cout << "Vai usar o framebuffer PostProcessing.... " << std::endl;

			std::string _filename = "teste.jpg";
			SOIL_save_screenshot(_filename.c_str(), SOIL_SAVE_TYPE_BMP, 0, 0, _width, _height);
			_postProcessing = 0;

			std::cout << "Voltou ao framebuffer Normal.... " << std::endl;
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
		else std::cout << "The effect could not be applied. Error in Framebuffer!" << std::endl;
	} 
	else glUseProgram(0);
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

	_width = glutGet(GLUT_WINDOW_WIDTH);
	_height = glutGet(GLUT_WINDOW_HEIGHT);

	// Mouse Over
	glm::vec2 mp = Input::getInstance()->getMousePostion();
	if( !Input::getInstance()->mouseWasPressed(GLUT_LEFT_BUTTON) && 
		!Input::getInstance()->mouseWasPressed(GLUT_RIGHT_BUTTON))
		glReadPixels(mp.x, glutGet(GLUT_WINDOW_HEIGHT) - mp.y - 1, 1, 1, GL_STENCIL_INDEX, 
					 GL_UNSIGNED_INT, &_stencilValue);

	// Taking screenshot
	if(Input::getInstance()->keyWasReleased('M')) {
		std::string _filename = "screenshots/screenshot";
		Utils::screenshot(_filename, _width, _height);
	}

	// Apply postprocessing
	if(Input::getInstance()->keyWasReleased('E')) {
		_postProcessing = 1;
	}
}


void GameManager::destroyBufferObjects(){
	ProgramShader::getInstance()->destroyShaderProgram();
	for (entityIterator i = _entities.begin(); i != _entities.end(); i++)
		i->second->~Entity();
	Camera::getInstance()->~Camera();
	glDeleteFramebuffers(1, &frameBufferPP);
}