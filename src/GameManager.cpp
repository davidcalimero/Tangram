#include "GameManager.h"



GameManager::GameManager(){
	_selected = NULL;
	_postProcessing = 0;
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


bool GameManager::isMouseOver(std::string id){
	if(_selected == NULL && id.compare("background") == 0) return true;
	if(_selected != NULL && _selected->getId().compare(id) == 0) return true;
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
	_quad = new Quad("plano");
	_quad->setMesh("mesh/quad.obj", "materials/quad.mtl");
	_quad->init();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	_light = new Light(glm::vec3(0-2.0,-2.0,2.0), 
					   glm::vec3(0.5,0.5,0.5), 
					   glm::vec3(0.9,0.9,0.9), 
					   glm::vec3(0.9,0.9,0.9));

	/**/
	Utils::loadScene("scene/currentScene.xml", "mesa", &qcoords, &pcoords);	
	Board * board = new Board("mesa");
	board->setMesh("mesh/plane.obj", "mesh/cube.obj", "materials/mesa.mtl");
	board->setTexture("materials/mesa.mtl");
	board->baseScale(2.2, 2.2, 0.0);
	board->borderScale(0.1, 2.1, 0.1);
	board->setTranslation(pcoords.x, pcoords.y, pcoords.z);	
	add(board);

	/**/
	Utils::loadScene("scene/currentScene.xml", "espelho", &qcoords, &pcoords);
	_mirror = new Mirror("espelho");
	_mirror->setMesh("mesh/cube.obj", "materials/espelho.mtl");
	_mirror->scale(2.0, 2.0, 0.0001);
	_mirror->setTranslation(pcoords.x, pcoords.y, pcoords.z);

	/**/
	Utils::loadScene("scene/currentScene.xml", "trianguloVermelho", &qcoords, &pcoords);
	TangramPieces * trianguloVermelho = new TangramPieces("trianguloVermelho");
	trianguloVermelho->setMesh("mesh/prism.obj", "materials/trianguloVermelho.mtl");
	trianguloVermelho->setTexture("materials/trianguloVermelho.mtl");
	trianguloVermelho->scale(sqrt(2.0)/2.0, sqrt(2.0)/2.0, 0.25);
	trianguloVermelho->setPos(pcoords.x, pcoords.y, pcoords.z, qcoords);
	add(trianguloVermelho);

	/**/
	Utils::loadScene("scene/currentScene.xml", "trianguloRoxo", &qcoords, &pcoords);
	TangramPieces * trianguloRoxo = new TangramPieces("trianguloRoxo");
	trianguloRoxo->setMesh("mesh/prism.obj", "materials/trianguloRoxo.mtl");
	trianguloRoxo->setTexture("materials/trianguloRoxo.mtl");
	trianguloRoxo->scale(sqrt(2.0)/2.0, sqrt(2.0)/2.0, 0.23);
	trianguloRoxo->setPos(pcoords.x, pcoords.y, pcoords.z, qcoords);
	add(trianguloRoxo);

	/**/
	Utils::loadScene("scene/currentScene.xml", "trianguloAzul", &qcoords, &pcoords);
	TangramPieces * trianguloAzul = new TangramPieces("trianguloAzul");
	trianguloAzul->setMesh("mesh/prism.obj", "materials/trianguloAzul.mtl");
	trianguloAzul->setTexture("materials/trianguloAzul.mtl");
	trianguloAzul->scale(1.0/2.0, 1.0/2.0, 0.13);
	trianguloAzul->setPos(pcoords.x, pcoords.y, pcoords.z, qcoords);
	add(trianguloAzul);

	/**/
	Utils::loadScene("scene/currentScene.xml", "trianguloVerde", &qcoords, &pcoords);
	TangramPieces * trianguloVerde = new TangramPieces("trianguloVerde");
	trianguloVerde->setMesh("mesh/prism.obj", "materials/trianguloVerde.mtl");
	trianguloVerde->setTexture("materials/trianguloVerde.mtl");
	trianguloVerde->scale(sqrt(2.0)/4.0, sqrt(2.0)/4.0, 0.21);
	trianguloVerde->setPos(pcoords.x, pcoords.y, pcoords.z, qcoords);
	add(trianguloVerde);

	/**/
	Utils::loadScene("scene/currentScene.xml", "trianguloRosa", &qcoords, &pcoords);
	TangramPieces * trianguloRosa = new TangramPieces("trianguloRosa");
	trianguloRosa->setMesh("mesh/prism.obj", "materials/trianguloRosa.mtl");
	trianguloRosa->setTexture("materials/trianguloRosa.mtl");
	trianguloRosa->scale(sqrt(2.0)/4.0, sqrt(2.0)/4.0, 0.17);
	trianguloRosa->setPos(pcoords.x, pcoords.y, pcoords.z, qcoords);
	add(trianguloRosa);

	/**/
	Utils::loadScene("scene/currentScene.xml", "quadradoLaranja", &qcoords, &pcoords);
	TangramPieces * quadradoLaranja = new TangramPieces("quadradoLaranja");
	quadradoLaranja->setMesh("mesh/cube.obj", "materials/quadradoLaranja.mtl");
	quadradoLaranja->setTexture("materials/quadradoLaranja.mtl");
	quadradoLaranja->scale(sqrt(2.0)/4.0, sqrt(2.0)/4.0, 0.19);
	quadradoLaranja->setPos(pcoords.x, pcoords.y, pcoords.z, qcoords);
	add(quadradoLaranja);

	/**/
	Utils::loadScene("scene/currentScene.xml", "quadradoAmarelo", &qcoords, &pcoords);
	TangramPieces * quadradoAmarelo = new TangramPieces("quadradoAmarelo");
	quadradoAmarelo->setMesh("mesh/parallellogram.obj", "materials/quadradoAmarelo.mtl");
	quadradoAmarelo->setTexture("materials/quadradoAmarelo.mtl");
	quadradoAmarelo->scale(1, 1, 0.15);
	quadradoAmarelo->setPos(pcoords.x, pcoords.y, pcoords.z, qcoords);
	add(quadradoAmarelo);
	/**/
}


void GameManager::draw(){
	ProgramShader::getInstance()->bind(_program);
	Camera::getInstance()->put();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	if(_postProcessing != 0){
		glBindFramebuffer(GL_FRAMEBUFFER, frameBufferPP);
		//Color Texture
		_quad->predraw();
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

	if(_postProcessing != 0) {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClearColor(0.1,0.1,0.1,1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		ProgramShader::getInstance()->bind(_postProgram);
		glUniform1i(ProgramShader::getInstance()->getId("tex"), 0);

		int width = glutGet(GLUT_WINDOW_WIDTH);
		int height = glutGet(GLUT_WINDOW_HEIGHT);
		std::cout << _postProcessing << std::endl;
		glUniform1i(ProgramShader::getInstance()->getId("width"), width);
		glUniform1i(ProgramShader::getInstance()->getId("height"), height);
		glUniform1i(ProgramShader::getInstance()->getId("effect"), _postProcessing);

		glDisable(GL_DEPTH_TEST);
		glDisable(GL_STENCIL_TEST);
	
		_quad->draw();
	
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

	// Apply postprocessing
	if(Input::getInstance()->specialWasReleased(GLUT_KEY_F1)) {
		if(_postProcessing == 1) _postProcessing = 0;
		else _postProcessing = 1;
	}
	if(Input::getInstance()->specialWasReleased(GLUT_KEY_F2)) {
		if(_postProcessing == 2) _postProcessing = 0;
		else _postProcessing = 2;
	}
	if(Input::getInstance()->specialWasReleased(GLUT_KEY_F3)) {
		if(_postProcessing == 3) _postProcessing = 0;
		else _postProcessing = 3;
	}
	if(Input::getInstance()->specialWasReleased(GLUT_KEY_F4)) {
		if(_postProcessing == 4) _postProcessing = 0;
		else _postProcessing = 4;
	}
	if(Input::getInstance()->specialWasReleased(GLUT_KEY_F5)) {
		if(_postProcessing == 5) _postProcessing = 0;
		else _postProcessing = 5;
	}
}



void GameManager::postProcessing(){

	int width = glutGet(GLUT_WINDOW_WIDTH);
	int height = glutGet(GLUT_WINDOW_HEIGHT);

	// Mouse Over
	glm::vec2 mp = Input::getInstance()->getMousePostion();
	if( !Input::getInstance()->mouseWasPressed(GLUT_LEFT_BUTTON) && 
		!Input::getInstance()->mouseWasPressed(GLUT_RIGHT_BUTTON)){
		GLuint stencilValue;
		glReadPixels(mp.x, height - mp.y - 1, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &stencilValue);
		int j = -1;
		Entity * temp = NULL;
		for(entityIterator i = _entities.begin(); i != _entities.end(); i++){
			if(j <= (int)(stencilValue-2)) j++;
			if(j == stencilValue-2) temp = i->second;
			if(_selected != NULL && _selected->getId().compare(i->first) == 0)
				_selected->activateAnimation();
			else i->second->desactivateAnimation();
		}
		if(j > -1 && temp != NULL) _selected = temp;
		else _selected = NULL;
	}

	// Taking screenshot
	if(Input::getInstance()->keyWasReleased('M')) {
		std::string _filename = "screenshots/screenshot";
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		Utils::screenshot(_filename, width, height);
	}
}


void GameManager::destroyBufferObjects(){
	ProgramShader::getInstance()->destroyShaderProgram();
	for (entityIterator i = _entities.begin(); i != _entities.end(); i++)
		i->second->~Entity();
	Camera::getInstance()->~Camera();
	glDeleteFramebuffers(1, &frameBufferPP);
}