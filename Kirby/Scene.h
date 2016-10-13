#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "PinxoEnemy.h"
#include "ProjectileObject.h"

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
	PinxoEnemy *mPinxoEnemy;
	ProjectileObject *mProjectileObject;
};


#endif // _SCENE_INCLUDE

