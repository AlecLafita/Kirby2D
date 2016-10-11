#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"
#include <GL/glut.h>

#define INIT_PLAYER_X_TILES 4
#define INIT_PLAYER_Y_TILES 4


Scene::Scene()
{
	map = NULL;
	player = NULL;
}

Scene::~Scene()
{
	if(map != NULL)
		delete map;
	if(player != NULL)
		delete player;
}


void Scene::init()
{
	initShaders();
	map = TileMap::createTileMap("levels/kawaii.txt", glm::vec2(0, 0), texProgram);
	player = new Player();
	player->setPathToSpriteSheet("images/bub.png");

	player->init(texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setTileMap(map);

	//ENEMY
	mBaseEnemy = new BaseEnemy();
	mBaseEnemy->setPathToSpriteSheet("images/kirby_spritesheet.png");
	mBaseEnemy->init(texProgram);
	mBaseEnemy->setPosition(glm::vec2(5 * map->getTileSize(), 5 * map->getTileSize()));
	mBaseEnemy->setTileMap(map);

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
	mBaseEnemy->update(deltaTime);
	mProjectileObject->update(deltaTime);
	//Update camera position
	glm::vec2 playerPos = player->getPosition();
	if (playerPos.x  < float(SCREEN_WIDTH - 1)/ 2) //left of the screen limit
		projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	else if (playerPos.x >(map->getMapWidth() - float(SCREEN_WIDTH - 1) / 2)) //right of the screen limit
		projection = glm::ortho(float(map->getMapWidth() - SCREEN_WIDTH - 1), float(map->getMapWidth()), float(SCREEN_HEIGHT - 1), 0.f);
	else
		projection = glm::ortho(playerPos.x - float(SCREEN_WIDTH - 1) / 2, playerPos.x + float(SCREEN_WIDTH - 1) / 2, float(SCREEN_HEIGHT - 1), 0.f);
}

void Scene::render() {
	glm::mat4 modelview;
	modelview = glm::mat4(1.0f);
	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	map->render();
	player->render();
	mBaseEnemy->render();
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



