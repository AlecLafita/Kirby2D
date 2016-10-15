#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "PinxoEnemy.h"
#include "ProjectileObject.h"
#include "ColisionHelper.h"

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
	bool collisionMoveRight(const glm::ivec2 &pos, const glm::ivec2 &size) const;
	bool collisionMoveLeft(const glm::ivec2 &pos, const glm::ivec2 &size) const;
	bool collisionMoveDown(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) const;
	bool collisionMoveUp(const glm::ivec2 &pos, const glm::ivec2 &size) const;
	bool playerCanSwallow(glm::ivec2 &pos) const;

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
	ColisionHelper* mColisionHelper;
};


#endif // _SCENE_INCLUDE

