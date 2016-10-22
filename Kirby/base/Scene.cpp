#include <iostream>
#include <fstream>
#include <sstream>
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

	mEnemies.clear();


	mProjectileObjects.clear();
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

	 mProjectileObjects.clear();

	 mEnemies.clear();
	//Texture spritesheetBg;
	//ShaderProgram texProgram;
}


void Scene::init(std::string levelPathFile, std::string backgroundPathFile, std::string enemiesLocationPathFile/*, std::string itemsLocationPathFile*/)
{
	resetScene();
	bToReset = false;

	initShaders();
	//Init helpers
	mColisionHelper = new ColisionHelper();
	mTransformationHelper = new TransformationHelper();

	//Init current map
	spritesheetBg.loadFromFile(backgroundPathFile, TEXTURE_PIXEL_FORMAT_RGBA);//May not need to be an attribute?
	map = TileMap::createTileMap(levelPathFile, glm::vec2(0, 0), texProgram);
	mBackground = Sprite::createSprite(glm::ivec2(map->getMapWidth(), map->getMapHeight()), glm::vec2(1, 1), &spritesheetBg, &texProgram);
	embellishmentMap = TileMap::createTileMap("levels/cloudy_lvl_no_collision.txt", glm::vec2(0, 0), texProgram);

	//Init characters, items
    player = new Kirby();
	player->init(texProgram, this);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	initEnemies(enemiesLocationPathFile);
	initObjects();

	//Init camera
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
	cameraLeftXposition = 0;
}

void Scene::update(int deltaTime)
{

	//TODO: Remove this. For testing purposes
	if (Game::instance().getKey('n')){
		Game::instance().nextLevel();
		return;
	}

	//TODO: Remove this. For testing purposes
    if(Game::instance().getKey('b')){

        player = new FireKirby();
        player->init(texProgram,this);
        player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
    }

	//Update game stuff
	currentTime += deltaTime;
	player->update(deltaTime);

	for (BaseEnemy* enemy : mEnemies) {
		enemy->update(deltaTime);
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
	for (set<BaseEnemy*>::iterator it = mEnemies.begin(); it != mEnemies.end();) {
		if ((*it)->isCharacterDead()) {
			mEnemies.erase(it++);
		}
		else ++it;
	}
	//Reset scene if needed (player with no energy)
	if (bToReset) {
		if (player->isBeingAnimated()) {

		} else {

			Game::instance().resetLevel();
		}
	}
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
	for (BaseEnemy* enemy : mEnemies) {
		enemy->render();
	}
	//render objects
	for (ProjectileObject* projectileObject : mProjectileObjects){
		projectileObject->render();
	}
}

//Collision functions, always call the helper to solve them: first check collision with tilemap,then check collision with other characters
bool Scene::collisionMoveRight(Character* character) const {
	bool mapCollision = mColisionHelper->mapMoveRight(map, character);
	bool enemyCollision = characterCollidesEnemies(character);
	return mapCollision || enemyCollision;
}
bool Scene::collisionMoveLeft(Character* character) const {
	bool mapCollision = mColisionHelper->mapMoveLeft(map, character);
	bool enemyCollision = characterCollidesEnemies(character);
	return mapCollision || enemyCollision;
}
bool Scene::collisionMoveDown(Character* character) const {
	bool mapCollision = mColisionHelper->mapMoveDown(map, character);
	//Maybe not return bool, if jumping on enemy kills it	
	bool enemyCollision = characterCollidesEnemies(character);
	return mapCollision || enemyCollision;
}
bool Scene::collisionMoveUp(Character* character) const {
	bool mapCollision = mColisionHelper->mapMoveUp(map, character);
	bool enemyCollision = characterCollidesEnemies(character);
	return mapCollision || enemyCollision;
}

bool Scene::characterCollidesEnemies(Character* character) const{
	bool collision = false; //Can be improved checking if true after each enemy and returning(with few enemies doesn't matter)

	for (BaseEnemy* enemy : mEnemies) {
		collision = collision || mColisionHelper->characterCollidesCharacter(enemy, character);
	}
	return collision;
}

bool Scene::collisionMoveRightOnlyMap(Character* character) const {
	return mColisionHelper->mapMoveRight(map, character);
}
bool Scene::collisionMoveLeftOnlyMap(Character* character) const {
	return mColisionHelper->mapMoveLeft(map, character);
}

bool Scene::playerCanSwallow(BaseEnemy* enemy) {
	if (!dynamic_cast<Kirby*>(player)) { //Kiry with ability -> can not swallow!
		return false;
	}

	bool hasSwallowed =  mColisionHelper->playerSwallowCharacter(player, enemy);
	if (hasSwallowed) {
        cout << "Just swallowed an enemy!" << endl;
		player = mTransformationHelper->transformPlayer(player, enemy,
                                                texProgram, this);
	}
	return hasSwallowed;
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
	fShader.initFromFile(FRAGMENT_SHADER,"shaders/texture.frag");
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
void Scene::initEnemies(std::string enemiesLocationPathFile){
	//read from enemies text file
	//file format: num of enemies
	//			   enemyType posX posY

	ifstream fin;
	string line;
	stringstream sstream;

	fin.open(enemiesLocationPathFile.c_str());
	if (!fin.is_open()) {
		cout << "file already open!" << endl;
		return;
	}
	getline(fin, line);
	sstream.str(line);
	int numEnemies;
	sstream >> numEnemies;
	cout << "num of enemies: " << numEnemies << endl;
	int enemyType, posX, posY;
	for (int i = 0; i < numEnemies; ++i) {
		getline(fin, line); //sstream.str(line);
		stringstream(line) >> enemyType >> posX >> posY;
		//cout << enemyType << " " << posX << " " << posY << endl;
		switch (enemyType) {
			case 0: {//pinxo 
				PinxoEnemy* mPinxoEnemy = new PinxoEnemy();
				mPinxoEnemy->init(texProgram, this);
				mPinxoEnemy->setPosition(glm::vec2(posX * map->getTileSize(), posY* map->getTileSize()));
				mEnemies.insert(mPinxoEnemy);
				break;
			}
			case 1: {//dummy fly
				FlyingDummyEnemy* mFlyingDummyEnemy = new FlyingDummyEnemy();
				mFlyingDummyEnemy->init(texProgram, this);
				mFlyingDummyEnemy->setPosition(glm::vec2(posX * map->getTileSize(), posY * map->getTileSize()));
				mEnemies.insert(mFlyingDummyEnemy);
				break;
			}
			case 2: { //dummy walk
				WalkingDummyEnemy* mWalkingEnemy = new WalkingDummyEnemy();
				mWalkingEnemy->init(texProgram, this);
				mWalkingEnemy->setPosition(glm::vec2(posX * map->getTileSize(), posY * map->getTileSize()));
				mEnemies.insert(mWalkingEnemy);
				break;
			}
			default:
				cout << "unknown enemy!" << endl;
				break;
		}
	}
}

//OBJECTS
void Scene::initObjects() {
	//read from enemies text file
	//file format: num of objects
	//			   objectType posX posY
	ProjectileObject* mProjectileObject = new ProjectileObject();
	mProjectileObject->setPathToSpriteSheet(OBJECTS_SPRITESHEET_PATH);
	mProjectileObject->setTexturePosition(glm::fvec2(0.25f, 0.25f));
	mProjectileObject->init(texProgram, this);
	mProjectileObject->setPosition(glm::vec2(10 * map->getTileSize(), 5 * map->getTileSize()));
	mProjectileObject->setDirection(glm::fvec2(1.0f, 0.0f));

	mProjectileObjects.insert(mProjectileObject);
}

