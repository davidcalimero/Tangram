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
	Utils::loadScene("sceneTest.xml", "tabuleiro", &qcoords, &pcoords);
	Board * board = new Board("tabuleiro", "cube.obj");
	board->scale(1.8, 1.8, 0.1);
	board->translate(pcoords.x, pcoords.y, pcoords.z);
	add(board);

	/**/
	Utils::loadScene("sceneTest.xml", "trianguloVermelho", &qcoords, &pcoords);
	TangramPieces * trianguloVermelho = new TangramPieces("trianguloVermelho", "prism.obj");
	trianguloVermelho->scale(sqrt(2.0)/2.0, sqrt(2.0)/2.0, 0.25);
	trianguloVermelho->setPos(pcoords.x, pcoords.y, pcoords.z, qcoords);
	add(trianguloVermelho);

	/**/
	Utils::loadScene("sceneTest.xml", "trianguloRoxo", &qcoords, &pcoords);
	TangramPieces * trianguloRoxo = new TangramPieces("trianguloRoxo", "prism.obj");
	trianguloRoxo->scale(sqrt(2.0)/2.0, sqrt(2.0)/2.0, 0.23);
	trianguloRoxo->setPos(pcoords.x, pcoords.y, pcoords.z, qcoords);
	add(trianguloRoxo);

	/**/
	Utils::loadScene("sceneTest.xml", "trianguloAzul", &qcoords, &pcoords);
	TangramPieces * trianguloAzul = new TangramPieces("trianguloAzul", "prism.obj");
	trianguloAzul->scale(1.0/2.0, 1.0/2.0, 0.13);
	trianguloAzul->setPos(pcoords.x, pcoords.y, pcoords.z, qcoords);
	add(trianguloAzul);

	/**/
	Utils::loadScene("sceneTest.xml", "trianguloVerde", &qcoords, &pcoords);
	TangramPieces * trianguloVerde = new TangramPieces("trianguloVerde", "prism.obj");
	trianguloVerde->scale(sqrt(2.0)/4.0, sqrt(2.0)/4.0, 0.21);
	trianguloVerde->setPos(pcoords.x, pcoords.y, pcoords.z, qcoords);
	add(trianguloVerde);

	/**/
	Utils::loadScene("sceneTest.xml", "trianguloRosa", &qcoords, &pcoords);
	TangramPieces * trianguloRosa = new TangramPieces("trianguloRosa", "prism.obj");
	trianguloRosa->scale(sqrt(2.0)/4.0, sqrt(2.0)/4.0, 0.17);
	trianguloRosa->setPos(pcoords.x, pcoords.y, pcoords.z, qcoords);
	add(trianguloRosa);

	/**/
	Utils::loadScene("sceneTest.xml", "quadradoLaranja", &qcoords, &pcoords);
	TangramPieces * quadradoLaranja = new TangramPieces("quadradoLaranja", "cube.obj");
	quadradoLaranja->scale(sqrt(2.0)/4.0, sqrt(2.0)/4.0, 0.19);
	quadradoLaranja->setPos(pcoords.x, pcoords.y, pcoords.z, qcoords);
	add(quadradoLaranja);

	/**/
	Utils::loadScene("sceneTest.xml", "quadradoAmarelo", &qcoords, &pcoords);
	TangramPieces * quadradoAmarelo = new TangramPieces("quadradoAmarelo", "cube.obj");
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

	glm::vec2 mp = Input::getInstance()->getMousePostion();
	if(!Input::getInstance()->mouseWasPressed(GLUT_LEFT_BUTTON) && !Input::getInstance()->mouseWasPressed(GLUT_RIGHT_BUTTON))
		glReadPixels(mp.x, glutGet(GLUT_WINDOW_HEIGHT) - mp.y - 1, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &_stencilValue);

	glUseProgram(0);
}


void GameManager::update(){
	Camera::getInstance()->update();
	for (entityIterator i = _entities.begin(); i != _entities.end(); i++)
		i->second->update();

	if(Input::getInstance()->keyWasPressed('G')) {
		TangramPieces * piece = (TangramPieces *) getEntityById("trianguloAzul");
		Utils::saveScene("sceneTest.xml", "trianguloAzul", piece->getQuat(), piece->getPos());
	}
}


void GameManager::destroyBufferObjects(){
	ProgramShader::getInstance()->destroyShaderProgram();
	for (entityIterator i = _entities.begin(); i != _entities.end(); i++)
		i->second->~Entity();
	Camera::getInstance()->~Camera();
}