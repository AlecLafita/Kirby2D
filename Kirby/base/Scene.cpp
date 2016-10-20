#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"
#include <GL/glut.h>

Scene::Scene()
{
	map = NULL;
	player = NULL;
	mColisionHelper = NULL;	
}

Scene::~Scene()
{
	if (map != NULL)
		delete map;
	if (embellishmentMap != NULL)
		delete embellishmentMap;
	if (player != NULL)
		delete player;
	if (mBackground != NULL)
		delete mBackground;
	if (mColisionHelper != NULL)
		delete mColisionHelper;

	mPinxoEnemies.clear();
	mProjectileObjects.clear();
	
	mSoundHelper = NULL;
	mGUI = NULL;
}

void Scene::resetScene() {
	if (map != NULL)
		delete map;
	if (embellishmentMap != NULL)
		delete embellishmentMap;
	if (player != NULL)
		delete player;
	if (mBackground != NULL)
		delete mBackground;
	if (mColisionHelper != NULL)
		delete mColisionHelper;

	 mPinxoEnemies.clear();
	 mProjectileObjects.clear();

	 mGUI = NULL;
	 mSoundHelper = NULL;

	//Texture spritesheetBg;
	//ShaderProgram texProgram;
}


void Scene::init(std::string levelPathFile, std::string backgroundPathFile/*, std::string enemiesLocationPathFile, std::string itemsLocationPathFile*/)
{
	resetScene();
	bToReset = false;

	initShaders();
	//Init helpers
	mColisionHelper = new ColisionHelper();

	//Init current map
	spritesheetBg.loadFromFile(backgroundPathFile, TEXTURE_PIXEL_FORMAT_RGBA);//May not need to be an attribute?
	map = TileMap::createTileMap(levelPathFile, glm::vec2(0, 0), texProgram);
	mBackground = Sprite::createSprite(glm::ivec2(map->getMapWidth(), map->getMapHeight()), glm::vec2(1, 1), &spritesheetBg, &texProgram);
	embellishmentMap = TileMap::createTileMap("levels/cloudy_lvl_no_collision.txt", glm::vec2(0, 0), texProgram);

	//Init characters, items
    player = new Kirby();
	player->init(texProgram,this);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	initEnemies();
	initObjects();

	//Init camera
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
	cameraLeftXposition = 0;
}

void Scene::update(int deltaTime)
{

	if (Game::instance().getKey('n')){ //TEST
		Game::instance().nextLevel();
		return;
	}

    if(Game::instance().getKey('b')){

        player = new BlackKirby();
        player->init(texProgram,this);
        player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
    }

	//Update game stuff
	currentTime += deltaTime;
	player->update(deltaTime);

	for (PinxoEnemy* pinxoEnemy : mPinxoEnemies) {
		pinxoEnemy->update(deltaTime);
	}
	for (ProjectileObject* projectileObject : mProjectileObjects){
		projectileObject->update(deltaTime);
	}

	//Update camera position
	glm::vec2 playerPos = player->getPosition();
	if (playerPos.x  < float(SCREEN_WIDTH - 1) / 2) //left of the screen limit
		cameraLeftXposition = 0;
	else if (playerPos.x >(map->getMapWidth() - float(SCREEN_WIDTH - 1) / 2)) //right of the screen limit
		cameraLeftXposition = map->getMapWidth() - SCREEN_WIDTH - 1;
	else //normal movement following the player
		cameraLeftXposition = playerPos.x - (SCREEN_WIDTH - 1) / 2;
	projection = glm::ortho(float(cameraLeftXposition), float(cameraLeftXposition + SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);

	//Delete dead enemies
	for (set<PinxoEnemy*>::iterator it = mPinxoEnemies.begin(); it != mPinxoEnemies.end();) {
		if ((*it)->isCharacterDead()) {
			mPinxoEnemies.erase(it++);
		}
		else ++it;
	}

	//Reset scene if needed (player with no energy)
	if (bToReset) Game::instance().resetLevel();
}

void Scene::render() {
	glm::mat4 modelview;
	modelview = glm::mat4(1.0f);
	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f); //Color uniform transform
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	mBackground->render();
	map->render();
    embellishmentMap->render();
	player->render();
	//render enemies
	for (PinxoEnemy* pinxoEnemy : mPinxoEnemies) {
		pinxoEnemy->render();
	}
	//render objects
	for (ProjectileObject* projectileObject : mProjectileObjects){
		projectileObject->render();
	}
}


//Collision functions, always call the helper to solve them:
	//First check collision with tilemap
	//Then check collision with other characters

bool Scene::collisionMoveRight(Character* character) const {
	bool mapCollision = mColisionHelper->mapMoveRight(map, character);
	
	bool enemyCollision = false;
	for (PinxoEnemy* pinxoEnemy : mPinxoEnemies) {
		enemyCollision = enemyCollision || mColisionHelper->characterCollidesCharacter(pinxoEnemy, character);
	}
	return mapCollision || enemyCollision;
}
bool Scene::collisionMoveLeft(Character* character) const {
	bool mapCollision = mColisionHelper->mapMoveLeft(map, character);

	bool enemyCollision = false;
	for (PinxoEnemy* pinxoEnemy : mPinxoEnemies) {
		enemyCollision = enemyCollision || mColisionHelper->characterCollidesCharacter(pinxoEnemy, character);
	}
	return mapCollision || enemyCollision;
}
bool Scene::collisionMoveDown(Character* character) const {
	bool mapCollision = mColisionHelper->mapMoveDown(map, character);

	//Maybe not return bool, if jumping on enemy kills it	
	bool enemyCollision = false;
	for (PinxoEnemy* pinxoEnemy : mPinxoEnemies) {
		enemyCollision = enemyCollision || mColisionHelper->characterCollidesCharacter(pinxoEnemy, character);
	}
	return mapCollision || enemyCollision;
}
bool Scene::collisionMoveUp(Character* character) const {
	bool mapCollision = mColisionHelper->mapMoveUp(map, character);
	bool enemyCollision = false;
	for (PinxoEnemy* pinxoEnemy : mPinxoEnemies) {
		enemyCollision = enemyCollision || mColisionHelper->characterCollidesCharacter(pinxoEnemy, character);
	}
	return mapCollision || enemyCollision;
}

bool Scene::collisionMoveRightOnlyMap(Character* character) const {
	return mColisionHelper->mapMoveRight(map, character);
}
bool Scene::collisionMoveLeftOnlyMap(Character* character) const {
	return mColisionHelper->mapMoveLeft(map, character);
}

bool Scene::playerCanSwallow(BaseEnemy* enemy) {
	bool justSwallow =  mColisionHelper->playerSwallowCharacter(player, enemy);
	if (justSwallow) {

	}
	return justSwallow;
}


//SHADERS
void Scene::initShaders(){
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if (!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}


//ENEMIES
void Scene::initEnemies(){
	//Jo faria una nova classe contenidora de tots els enemics que s'encarregues de init,update i render

	//read from enemies text file
	PinxoEnemy* mPinxoEnemy = new PinxoEnemy();
	mPinxoEnemy->init(texProgram, this);
	mPinxoEnemy->setPosition(glm::vec2(5 * map->getTileSize(), 5 * map->getTileSize()));
	mPinxoEnemies.insert(mPinxoEnemy);
	initObjects();
}

//OBJECTS
void Scene::initObjects() {
	//read from objects text file
	ProjectileObject* mProjectileObject = new ProjectileObject();
	mProjectileObject->setTexturePosition(glm::fvec2(0.25f, 0.25f));
	mProjectileObject->init(texProgram, this);
	mProjectileObject->setPosition(glm::vec2(10 * map->getTileSize(), 5 * map->getTileSize()));
	mProjectileObject->setDirection(glm::fvec2(1.0f, 0.0f));

	mProjectileObjects.insert(mProjectileObject);
}

//GUI
void Scene::setPlayerEnergy(int energy) {
	mGUI->setPlayerEnergy(energy);
}
