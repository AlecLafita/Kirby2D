#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "../characters/Player.h"
#include "../objects/BaseObject.h"
#include "../helpers/ColisionHelper.h"
#include "../helpers/TransformationHelper.h"
#include "Defines.h"

class PortalObject;
class DoorObject;

#include <set>

// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();

	void init(std::string levelPathFile, std::string backgroundPathFile, std::string enemiesLocationPathFile, std::string itemsLocationPathFile);
	void update(int deltaTime);
	void render();

	void resetScene();
	void setSceneToReset() { bToReset = true; };

	//Collision functions
	bool collisionMoveRight(Character* character) const;
	bool collisionMoveLeft(Character* character) const;
	bool collisionMoveDown(Character* character) const;
	bool collisionMoveUp(Character* character) const;

	bool collisionCanFall(BaseEnemy* enemy) const;

	bool collisionMoveRightOnlyMap(Character* character) const;
	bool collisionMoveLeftOnlyMap(Character* character) const;

	bool playerCanKill(BaseEnemy* enemy) ;

	bool playerTakesItem(BaseObject* obj);
	bool playerTakesDoorNextLevel(DoorObject* obj);

	void characterTakesPortal(PortalObject* p);

	int getCameraLeftPosition() const { return cameraLeftXposition; }
	Player* getPlayer(){ return  player;}

private:
	void initShaders();
	void initEnemies(std::string enemiesLocationPathFile);
	void initObjects(std::string itemsLocationPathFile);

	bool characterCollidesEnemies(Character* character) const;

	void loseAbility();
private:
	bool bToReset;
    bool bGoToNextLevel;
	TileMap *map; //Don't render this! only for collisions
	TileMap *embellishmentMap; //Reneder this, not use it for collisions!
    Sprite *mBackground;
	Texture spritesheetBg;
	Player *player;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	set<BaseEnemy*> mEnemies;
	set<BaseObject*> mPowerUps;
	vector<PortalObject* > mPortals1;
	vector<PortalObject* > mPortals2;
	ColisionHelper* mColisionHelper;
	TransformationHelper* mTransformationHelper;

	BaseObject* mDoorNextLvl;
	int cameraLeftXposition;

};


#endif // _SCENE_INCLUDE

