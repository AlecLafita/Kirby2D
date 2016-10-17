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
	if(map != NULL)
		delete map;
	if(player != NULL)
		delete player;
    if(embellishmentMap != NULL)
        delete embellishmentMap;
    if(mSoundHelper != NULL)
        delete mSoundHelper;
}


void Scene::init()
{
	initShaders();

	mColisionHelper = new ColisionHelper();
	mSoundHelper = new SoundHelper();

	//mSoundHelper->playMusic("sounds/song_green_greens.wav");

	spritesheetBg.loadFromFile("images/peppermint_palace.png", TEXTURE_PIXEL_FORMAT_RGBA);
	map = TileMap::createTileMap("levels/Cloudy_lvl.txt", glm::vec2(0, 0), texProgram);
	mBackground = Sprite::createSprite(glm::ivec2(map->getMapWidth(), map->getMapHeight()), glm::vec2(1, 1), &spritesheetBg, &texProgram);
    embellishmentMap = TileMap::createTileMap("levels/cloudy_lvl_no_collision.txt", glm::vec2(0, 0), texProgram);


    player = new Player();
	player->setPathToSpriteSheet("images/kirby_spritesheet.png");

	player->init(texProgram,this);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));

	//ENEMY
	PinxoEnemy* mPinxoEnemy = new PinxoEnemy();
    mPinxoEnemy->init(texProgram,this);
    mPinxoEnemy->setPosition(glm::vec2(5 * map->getTileSize(), 5 * map->getTileSize()));
	mPinxoEnemies.insert(mPinxoEnemy);
	//ITEM
	ProjectileObject* mProjectileObject = new ProjectileObject();
	mProjectileObject->setPathToSpriteSheet("images/items.png");
	mProjectileObject->setTexturePosition(glm::fvec2(0.25f, 0.25f));
	mProjectileObject->init(texProgram, this);
	mProjectileObject->setPosition(glm::vec2(10 * map->getTileSize(), 5 * map->getTileSize()));
	mProjectileObject->setDirection(glm::fvec2(1.0f,0.0f));

	mProjectileObjects.insert(mProjectileObject);

	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;

	cameraLeftXposition = 0;

	mGUI = new GUI();
	mGUI->init();
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	player->update(deltaTime);

	for (PinxoEnemy* pinxoEnemy : mPinxoEnemies) {
		pinxoEnemy->update(deltaTime);
	}
	for (ProjectileObject* projectileObject : mProjectileObjects){
		projectileObject->update(deltaTime);
	}

	//Delete dead enemies
	for (set<PinxoEnemy*>::iterator it = mPinxoEnemies.begin(); it != mPinxoEnemies.end(); ) {
		if ((*it)->isCharacterDead()) {
			mPinxoEnemies.erase(it++);
		}
		else ++it;
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
	for (PinxoEnemy* pinxoEnemy : mPinxoEnemies) {
		pinxoEnemy->render();
	}
	for (ProjectileObject* projectileObject : mProjectileObjects){
		projectileObject->render();
	}
	mGUI->render();
}

void Scene::initShaders(){
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if(!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}


//Collision functions, always call the helper to solve them:
	//First check collision with tilemap
	//Then check collision with other characters

bool Scene::collisionMoveRight(Character* character) const {
	bool mapCollision = mColisionHelper->mapMoveRight(map, character);
	
	bool enemyCollision = false;
	for (PinxoEnemy* pinxoEnemy : mPinxoEnemies) {
		enemyCollision = enemyCollision || mColisionHelper->characterMoveRight(pinxoEnemy, character);
	}
	return mapCollision || enemyCollision;
}

bool Scene::collisionMoveLeft(Character* character) const {
	bool mapCollision = mColisionHelper->mapMoveLeft(map, character);

	bool enemyCollision = false;
	for (PinxoEnemy* pinxoEnemy : mPinxoEnemies) {
		enemyCollision = enemyCollision || mColisionHelper->characterMoveLeft(pinxoEnemy, character);
	}
	return mapCollision || enemyCollision;
}

bool Scene::collisionMoveDown(Character* character) const {
	bool mapCollision = mColisionHelper->mapMoveDown(map, character);

	//Maybe not return bool, if jumping on enemy kills it	
	bool enemyCollision = false;
	for (PinxoEnemy* pinxoEnemy : mPinxoEnemies) {
		enemyCollision = enemyCollision || mColisionHelper->characterMoveDown(pinxoEnemy, character);
	}
	return mapCollision || enemyCollision;
}
bool Scene::collisionMoveUp(Character* character) const {
	bool mapCollision = mColisionHelper->mapMoveUp(map, character);
	bool enemyCollision = false;
	for (PinxoEnemy* pinxoEnemy : mPinxoEnemies) {
		enemyCollision = enemyCollision || mColisionHelper->characterMoveUp(pinxoEnemy, character);
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


// Sound!
void Scene::playSound(string soundFilePath) {

    //mSoundHelper->playSound(soundFilePath);
}

void Scene::stopSound() {

    //mSoundHelper->stopSound();
}

//GUI
void Scene::setPlayerEnergy(int energy) {
	mGUI->setPlayerEnergy(energy);
}
