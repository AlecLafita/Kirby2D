#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "helpers/SoundHelper.h"
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "PinxoEnemy.h"
#include "ProjectileObject.h"
#include "ColisionHelper.h"
#include "Constants.h"
#include "GUI.h"

#include <set>

// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();

	void init();
	void update(int deltaTime);
	void render();

	//Collision functions
	bool collisionMoveRight(Character* character) const;
	bool collisionMoveLeft(Character* character) const;
	bool collisionMoveDown(Character* character) const;
	bool collisionMoveUp(Character* character) const;

	bool collisionMoveRightOnlyMap(Character* character) const;
	bool collisionMoveLeftOnlyMap(Character* character) const;

	bool playerCanSwallow(BaseEnemy* enemy) ;

	//GUI functions
	void substractEnergy();

	int getCameraLeftPosition() const { return cameraLeftXposition; }

	//Sound functions
	void playSound(string soundFilePath);

private:
	void initShaders();

private:
	TileMap *map;
	TileMap *embellishmentMap;
    Sprite *mBackground;
	Texture spritesheetBg;
	Player *player;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	set<PinxoEnemy*> mPinxoEnemies;
	set<ProjectileObject*> mProjectileObjects;
	ColisionHelper* mColisionHelper;
	SoundHelper* mSoundHelper;
	GUI* mGUI;

	int cameraLeftXposition;
};


#endif // _SCENE_INCLUDE

