#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"
#include <GL/glut.h>

#define INIT_PLAYER_X_TILES 2
#define INIT_PLAYER_Y_TILES 2


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
}


void Scene::init()
{
	initShaders();

	mColisionHelper = new ColisionHelper();

	spritesheetBg.loadFromFile("images/peppermint_palace.png", TEXTURE_PIXEL_FORMAT_RGBA);
	map = TileMap::createTileMap("levels/Cloudy_lvl.txt", glm::vec2(0, 0), texProgram);
	mBackground = Sprite::createSprite(glm::ivec2(map->getMapWidth(), map->getMapHeight()), glm::vec2(1, 1), &spritesheetBg, &texProgram);
    embellishmentMap = TileMap::createTileMap("levels/cloudy_lvl_no_collision.txt", glm::vec2(0, 0), texProgram);


    player = new Player();
	player->setPathToSpriteSheet("images/kirby_spritesheet.png");

	player->init(texProgram,this);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));

	//ENEMY
	mPinxoEnemy = new PinxoEnemy();
    mPinxoEnemy->init(texProgram,this);
    mPinxoEnemy->setPosition(glm::vec2(5 * map->getTileSize(), 5 * map->getTileSize()));

	//ITEM
	mProjectileObject = new ProjectileObject();
	mProjectileObject->setPathToSpriteSheet("images/items.png");
	mProjectileObject->setTexturePosition(glm::fvec2(0.25f, 0.25f));
	mProjectileObject->init(texProgram);
	mProjectileObject->setPosition(glm::vec2(10 * map->getTileSize(), 5 * map->getTileSize()));
	mProjectileObject->setDirection(glm::fvec2(1.0f,0.0f));
	mProjectileObject->setTileMap(map);


	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	player->update(deltaTime);
    mPinxoEnemy->update(deltaTime);
	mProjectileObject->update(deltaTime);
	//Update camera position
	glm::vec2 playerPos = player->getPosition();
	if (playerPos.x  < float(SCREEN_WIDTH - 1)/ 2) //left of the screen limit
		projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	else if (playerPos.x >(map->getMapWidth() - float(SCREEN_WIDTH - 1) / 2)) //right of the screen limit
		projection = glm::ortho(float(map->getMapWidth() - SCREEN_WIDTH - 1), float(map->getMapWidth()), float(SCREEN_HEIGHT - 1), 0.f);
	else //normal movement following the player
		projection = glm::ortho(playerPos.x - float(SCREEN_WIDTH - 1) / 2, playerPos.x + float(SCREEN_WIDTH - 1) / 2, float(SCREEN_HEIGHT - 1), 0.f);
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
    mPinxoEnemy->render();
	mProjectileObject->render();
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

//size hauria de ser el tamany de qui mira el collide(el player) no del tile map!! 
bool Scene::collisionMoveRight(const glm::ivec2 &pos, const glm::ivec2 &size) const {
	bool mapCollision = mColisionHelper->mapMoveRight(map, pos, size);
	//Iterate through all enemies
	bool enemyCollision = mColisionHelper->characterMoveRight(mPinxoEnemy, pos,size);
	
	return mapCollision || enemyCollision;
}

bool Scene::collisionMoveLeft(const glm::ivec2 &pos, const glm::ivec2 &size) const {
	bool mapCollision = mColisionHelper->mapMoveLeft(map, pos, size);
	bool enemyCollision = mColisionHelper->characterMoveLeft(mPinxoEnemy, pos, size);

	return mapCollision || enemyCollision;
}

bool Scene::collisionMoveDown(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) const {
	bool mapCollision = mColisionHelper->mapMoveDown(map, pos, size,posY);
	
	//Maybe not return bool, if jumping on emey kills it	
	bool enemyCollision = mColisionHelper->characterMoveDown(mPinxoEnemy, pos, size,posY);

	return mapCollision || enemyCollision;
}
bool Scene::collisionMoveUp(const glm::ivec2 &pos, const glm::ivec2 &size) const {
	bool mapCollision = mColisionHelper->mapMoveUp(map, pos, size);
	bool enemyCollision = mColisionHelper->characterMoveUp(mPinxoEnemy, pos, size);

	return mapCollision || enemyCollision;
}