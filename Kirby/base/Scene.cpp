#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"
#include <GL/glut.h>

#include <glm/glm.hpp>

#include "../characters/BlackKirby.h"
#include "../characters/FireKirby.h"
#include "../characters/Kirby.h"
#include "../characters/PinxoEnemy.h"
#include "../characters/FlyingDummyEnemy.h"
#include "../characters/WalkingDummyEnemy.h"
#include "../characters/FireEnemy.h"
#include "../characters/IcyEnemy.h"
#include "../characters/AttackEnemy.h"
#include "../characters/AquaEnemy.h"

#include "../objects/EnergyObject.h"
#include "../objects/LifeObject.h"
#include "../objects/SquareTileObject.h"
#include "../objects/PortalObject.h"
#include "../objects/DoorObject.h"

Scene::Scene()
{
	map = NULL;
	player = NULL;
	mColisionHelper = NULL;
	mDoorNextLvl = NULL;
}

Scene::~Scene()
{
	resetScene();
}

void Scene::resetScene() {
	if (map != NULL)
		delete map;

	/*if (embellishmentMap != NULL)
		delete embellishmentMap;
		cout << "embillmap" << endl;*/

	if (player != NULL)
		delete player;

	if (mBackground != NULL)
		delete mBackground;

	if (mColisionHelper != NULL)
		delete mColisionHelper;

	mPowerUps.clear();
	mEnemies.clear();
	mPortals1.clear();
	mPortals2.clear();
	mDoorNextLvl = NULL;
	mSquareTilesObjs.clear();
	//Texture spritesheetBg;
	//ShaderProgram texProgram;
}


void Scene::init(std::string levelPathFile, std::string backgroundPathFile, std::string enemiesLocationPathFile, std::string itemsLocationPathFile)
{
	resetScene();
	bToReset = false;
    bGoToNextLevel = false;

	initShaders();

	//Init helpers
	mColisionHelper = new ColisionHelper();
	mTransformationHelper = new TransformationHelper();

	//Init current map
	spritesheetBg.loadFromFile(backgroundPathFile, TEXTURE_PIXEL_FORMAT_RGBA);//May not need to be an attribute?
	map = TileMap::createTileMap(levelPathFile + ".txt", glm::vec2(0, 0), texProgram);
	mBackground = Sprite::createSprite(glm::ivec2(map->getMapWidth(), map->getMapHeight()), glm::vec2(1, 1), &spritesheetBg, &texProgram);
	embellishmentMap = TileMap::createTileMap(levelPathFile + "_no_cols.txt", glm::vec2(0, 0), texProgram);

	//Init characters, items
    player = new Kirby();
	player->init(texProgram, this);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	Game::instance().setAbilityToShow(PowerType::Normal);//Set as normal Kirby
	initEnemies(enemiesLocationPathFile);
	initObjects(itemsLocationPathFile);

	//Init camera
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
	cameraLeftXposition = 0;
}

void Scene::update(int deltaTime)
{


	//TODO: Remove this. For testing purposes
	if (bGoToNextLevel){
		Game::instance().playSound(SOUND_ENTER_DOOR);
        Game::instance().nextLevel();
		return;
	}

	// --------------- LOSE ABILITY ---------------
	if (Game::instance().getKey('H') || Game::instance().getKey('h')){
		loseAbility();
    }

	//Update game stuff
	currentTime += deltaTime;
	player->update(deltaTime);

    if(mDoorNextLvl != NULL){

		mDoorNextLvl->update(deltaTime);
    }

	for (BaseEnemy* enemy : mEnemies) {
		enemy->update(deltaTime);
	}
	for (BaseObject* object : mPowerUps){
		object->update(deltaTime);
	}
	for (PortalObject* portal : mPortals1) {
		portal->update(deltaTime);
	}
	for (PortalObject* portal : mPortals2) {
		portal->update(deltaTime);
	}
	for(BaseObject* square : mSquareTilesObjs){
		square->update(deltaTime);
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
			Game::instance().addScore((*it)->getScore());
			mEnemies.erase(it++);
		}
		else ++it;
	}
	//Delete taken objects
	for (set<BaseObject*>::iterator it = mPowerUps.begin(); it != mPowerUps.end();) {
		if ((*it)->isTaken()) {
			Game::instance().addScore((*it)->getScore());
			mPowerUps.erase(it++);
		}
		else ++it;
	}
	for (set<BaseObject*>::iterator it = mSquareTilesObjs.begin(); it != mSquareTilesObjs.end();) {
		if ((*it)->isTaken()) {
			Game::instance().addScore((*it)->getScore());
			mSquareTilesObjs.erase(it++);
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
	map->render(); //should be commented!
    embellishmentMap->render();
	player->render();
	//render enemies
	for (BaseEnemy* enemy : mEnemies) {
		enemy->render();
	}
	//render objects
	for (BaseObject* projectileObject : mPowerUps){
		projectileObject->render();
	}
	for (BaseObject* squareObj : mSquareTilesObjs){
		squareObj->render();
	}
	for (PortalObject* portal : mPortals1) {
		portal->render();
	}
	for (PortalObject* portal : mPortals2) {
		portal->render();
	}

}

//Collision functions, always call the helper to solve them: first check collision with tilemap,then check collision with other characters
bool Scene::collisionMoveRight(Character* character) const {
	bool mapCollision = mColisionHelper->mapMoveRight(map, character);
	bool enemyCollision = characterCollidesEnemies(character);
    bool tilesCollision = characterCollidesTiles(character);
	return mapCollision || enemyCollision || tilesCollision;
}

bool Scene::collisionMoveLeft(Character* character) const {
	bool mapCollision = mColisionHelper->mapMoveLeft(map, character);
	bool enemyCollision = characterCollidesEnemies(character);
    bool tilesCollision = characterCollidesTiles(character);
    return mapCollision || enemyCollision || tilesCollision;
}
bool Scene::collisionMoveDown(Character* character) const {
	bool mapCollision = mColisionHelper->mapMoveDown(map, character);
	bool enemyCollision = characterCollidesEnemies(character);
    bool tilesCollision = characterCollidesTiles(character);
    if (!mapCollision && tilesCollision) {
    	glm::ivec2 posChar = character->getPosition();
    	character->setPosition(glm::ivec2(posChar.x, posChar.y - FALL_STEP));
    }
    return mapCollision || enemyCollision || tilesCollision;
}
bool Scene::collisionMoveUp(Character* character) const {
	bool mapCollision = mColisionHelper->mapMoveUp(map, character);
	bool enemyCollision = characterCollidesEnemies(character);
    bool tilesCollision = characterCollidesTiles(character);
    return mapCollision || enemyCollision || tilesCollision;
}

bool Scene::collisionCanFall(BaseEnemy* enemy) const {
	return mColisionHelper->mapFalls(map, enemy);
}


bool Scene::characterCollidesTiles(Character* character) const{

    bool collision = false;
    for(BaseObject* tileQuad : mSquareTilesObjs){

        collision = collision || mColisionHelper->characterCollidesObject(character, tileQuad);
    }
    return collision;
}

bool Scene::characterCollidesEnemies(Character* character) const{
	bool collision = false; //Can be improved checking if true after each enemy and returning(with few enemies doesn't matter)

    int posEnemyX = character->getPosition().x;
    bool collidedEnemy = false;
	for (BaseEnemy* enemy : mEnemies) {
        collidedEnemy = mColisionHelper->characterCollidesCharacter(enemy, character);
		collision = collision || collidedEnemy;
		if(collidedEnemy){
            posEnemyX = enemy->getPosition().x;
            break;
        }
        if (AttackEnemy* aEnemy = dynamic_cast<AttackEnemy*>(enemy)){
			collidedEnemy = collision || mColisionHelper->characterCollidesObject(character, aEnemy->getAttack());
			collision = collision || collidedEnemy;
			if(collidedEnemy){
	            posEnemyX = (aEnemy->getAttack())->getPosition().x;
	            break;
	        }
		}
        
	}

	Player *p = dynamic_cast<Player*>(character);
	if (p && collision) {
        //enemies can not get damaged between them!
        int diffInX = (character->getPosition().x - posEnemyX);
        p->justDamaged(diffInX > 0);
    }
	return collision;
}

bool Scene::collisionMoveRightOnlyMap(Character* character) const {
	return mColisionHelper->mapMoveRight(map, character);
}
bool Scene::collisionMoveLeftOnlyMap(Character* character) const {
	return mColisionHelper->mapMoveLeft(map, character);
}

bool Scene::playerCanSwallow(BaseObject* baseObj){

	if (Kirby* k = dynamic_cast<Kirby*>(player)) {
		bool hasSwallowed = mColisionHelper->playerSwallowObject(player, baseObj);
		if (hasSwallowed) {
			Game::instance().stopSound(SOUND_VACUUMING);
		}
		return hasSwallowed;
	}
}

bool Scene::playerCanKill(BaseEnemy* enemy) {

    bool result;

    if (Kirby* k = dynamic_cast<Kirby*>(player)) { //normal Kiry -> swallow!
		bool hasSwallowed = mColisionHelper->playerSwallowCharacter(player, enemy);
		if (hasSwallowed) {
			Game::instance().stopSound(SOUND_VACUUMING);
			player->playTransformationSound();
			if (enemy->getType() == PowerType::Normal) Game::instance().stopSound(SOUND_TRANSFORMATION);
			player = mTransformationHelper->transformPlayer(player, enemy,
				texProgram, this);
			Game::instance().setAbilityToShow(enemy->getType());
		}
		return hasSwallowed;
	}

	else if (FireKirby* f = dynamic_cast<FireKirby*> (player))
		result = mColisionHelper->characterCollidesObject(enemy,f->getFire());

	else if (IceKirby* iceK = dynamic_cast<IceKirby*> (player)) 
		result = mColisionHelper->characterCollidesObject(enemy,iceK->getIce());

	else if (AquaKirby* aquaK = dynamic_cast<AquaKirby*> (player))
		result = mColisionHelper->characterCollidesObject(enemy,aquaK->getAqua());

    if(result){

        Game::instance().playSound(SOUND_DAMAGE);
    }
	return result;
}



bool Scene::playerTakesItem(BaseObject* obj) {
	if (mColisionHelper->characterCollidesObject(player, obj)) { 
		if (EnergyObject* o = dynamic_cast<EnergyObject*>(obj)) { //recover energy
			if (o->recoversFullEnergy()) { //tomato
				player->recoverEnergy(MAX_ENERGY);
			}
			else  player->recoverEnergy(1);//other food
		}
		else if (LifeObject* o = dynamic_cast<LifeObject*>(obj)) {//recoverLife
			Game::instance().winLife();
		}
		return true;
	}
	return false;
}

void Scene::elementTakesPortal(PortalObject* p) {
	//player
	int index = p->getIndex();
	if ( p->getType())
		mColisionHelper->characterDoesTeleport(player,mPortals1[index],mPortals2[index]);
	else
		mColisionHelper->characterDoesTeleport(player,mPortals2[index],mPortals1[index]);

	//enemies
	for (BaseEnemy* enemy : mEnemies) {
		if ( p->getType())
			mColisionHelper->characterDoesTeleport(enemy,mPortals1[index],mPortals2[index]);
		else
			mColisionHelper->characterDoesTeleport(enemy,mPortals2[index],mPortals1[index]);
	}
}

bool Scene::playerTakesDoorNextLevel(DoorObject *obj) {

	if (mColisionHelper->characterCollidesObject(player, obj)) {

        bGoToNextLevel = true;
	}
	return bGoToNextLevel;
}

bool Scene::objectCollides(BaseObject *o) { //ADD collision with enemies too?
	return (mColisionHelper->characterCollidesObject(player, o) || 
		mColisionHelper->mapCollidesObject(map,o));
}

void Scene::loseAbility() {
	if (Kirby* k = dynamic_cast<Kirby*>(player)) {
        //TODO Laura: This is horrible. How to make diff in casts?
    } else {

        PinxoEnemy* dummyPinxo = new PinxoEnemy();
        player = mTransformationHelper->transformPlayer(player, dummyPinxo, texProgram, this);
        Game::instance().setAbilityToShow(dummyPinxo->getType());
        player->playTransformationSound();
        delete dummyPinxo;
    }
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
	//cout << "num of enemies: " << numEnemies << endl;
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
			case 3:{ //Fire
				FireEnemy* fireEnemy = new FireEnemy();
                fireEnemy->init(texProgram, this);
                fireEnemy->setPosition(glm::vec2(posX * map->getTileSize(), posY * map->getTileSize()));
				mEnemies.insert(fireEnemy);
				break;
			}

            case 4: { // Ice enemy
                IcyEnemy* icyEnemy = new IcyEnemy();
                icyEnemy->init(texProgram, this);
                icyEnemy->setPosition(glm::vec2(posX * map->getTileSize(), posY * map->getTileSize()));
                mEnemies.insert(icyEnemy);
				break;
            }
            case 5: { // Aqua enemy
                AquaEnemy* aquaEnemy = new AquaEnemy();
				aquaEnemy->init(texProgram, this);
				aquaEnemy->setPosition(glm::vec2(posX * map->getTileSize(), posY * map->getTileSize()));
                mEnemies.insert(aquaEnemy);
				break;
            }
			default:
				cout << "unknown enemy!" << endl;
				break;
		}
	}

	fin.close();
}

//OBJECTS
void Scene::initObjects(std::string itemsLocationPathFile) {
	//read from enemies text file
	//file format: num of objects
	//			   objectType posX posY

	ifstream fin;
	string line;
	stringstream sstream;

	fin.open(itemsLocationPathFile.c_str());
	if (!fin.is_open()) {
		cout << "file already open!" << endl;
		return;
	}
	getline(fin, line);
	sstream.str(line);
	int numObjects;
	sstream >> numObjects;
	//cout << "num of objects: " << numObjects << endl;
	int objectType, posX, posY;
	for (int i = 0; i < numObjects; ++i) {
		getline(fin, line); //sstream.str(line);
		stringstream(line) >> objectType >> posX >> posY;
		//cout << objectType << " " << posX << " " << posY << endl;
		switch (objectType) {
            case 0: {// 1 energy recovery -> diverse food
                EnergyObject *oneEnergyRecovery = new EnergyObject();
                oneEnergyRecovery->init(texProgram, this);
                oneEnergyRecovery->setPosition(glm::vec2(posX * map->getTileSize(), posY * map->getTileSize()));
                oneEnergyRecovery->setFullRecovery(false);
                mPowerUps.insert(oneEnergyRecovery);
                break;
            }
            case 1: { //full energy recovery ->tomato
                EnergyObject *fullEnergyRecovery = new EnergyObject();
                fullEnergyRecovery->setFullRecovery(true);
                fullEnergyRecovery->init(texProgram, this);
                fullEnergyRecovery->setPosition(glm::vec2(posX * map->getTileSize(), posY * map->getTileSize()));
                mPowerUps.insert(fullEnergyRecovery);
                break;
            }
            case 2: { //life recovery
                LifeObject *lifeRecovery = new LifeObject();
                lifeRecovery->init(texProgram, this);
                lifeRecovery->setPosition(glm::vec2(posX * map->getTileSize(), posY * map->getTileSize()));
                mPowerUps.insert(lifeRecovery);
                break;
            }
            case 3: { // Door
                mDoorNextLvl = new DoorObject();
                mDoorNextLvl->init(texProgram, this);
                mDoorNextLvl->setPosition(glm::vec2(posX * map->getTileSize(), posY * map->getTileSize()));
                break;
            }
            case 4: { // Square tile
                SquareTileObject *squaredTile = new SquareTileObject();
                squaredTile->init(texProgram, this);
                squaredTile->setPosition(glm::vec2(posX * map->getTileSize(), posY * map->getTileSize()));
                mSquareTilesObjs.insert(squaredTile);
                break;
            }
            default:
                cout << "unknown item!" << endl;
                break;
        }
	}

	//Read portals
	//Number of pairs of portals
	//	PositionPortal1(x,y) PositionPortal2(x,y) 
	int numPortals;
	getline(fin, line);
	stringstream(line) >> numPortals;
	cout << "num of portals: " << numPortals << endl;
	mPortals1.resize(numPortals);
	mPortals2.resize(numPortals);
	int posXP1, posYP1, posXP2, posYP2;
	for (int i = 0; i < numPortals; ++i) {
		getline(fin, line);
		stringstream(line) >> posXP1 >> posYP1 >> posXP2 >> posYP2;

		PortalObject* portal1 = new PortalObject(true,i);
		portal1->init(texProgram,this);
		portal1->setPosition(glm::vec2(posXP1 * map->getTileSize(), posYP1 * map->getTileSize()));

		PortalObject* portal2 = new PortalObject(false,i);
		portal2->init(texProgram,this);
		portal2->setPosition(glm::vec2(posXP2 * map->getTileSize(), posYP2 * map->getTileSize()));

		mPortals1[i] = portal1;
		mPortals2[i] = portal2;
	}

	fin.close();
}

