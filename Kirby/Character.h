#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE

#include "Sprite.h"
#include "TileMap.h"

#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 70
#define FALL_STEP 4


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.

enum BasicPlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT
};

class Character
{

public:
	Character();
	~Character(){}

	void init(ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();
	
	void setTileMap(TileMap *tileMap);
	void setPathToSpriteSheet(string pathToSpriteSheet);//must be called before init
	void setPosition(const glm::vec2 &pos);
	glm::vec2 getPosition();

protected:

	bool bJumping;
	glm::ivec2 posCharacter;
	int jumpAngle, startY;
	string mPathToSpritesheet;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
	int mNumberAnimations, mSpriteColumns, mSpriteRows;
    int mNumStandLeft, mNumStandRight; // Number of stand left/right sprites
    int mNumMoveLeft, mNumMoveRight; // Number of move left/right sprites
    int mNumAttackLeft, mNumAttackRight; // Number of attack left/right sprites

    // Constants
    int START_ROW_STAND_RIGHT;
    int START_ROW_STAND_LEFT;
    int START_ROW_MOVE_RIGHT;
    int START_ROW_MOVE_LEFT;
    int START_ROW_ATTACK_RIGHT;
    int START_ROW_ATTACK_LEFT;
};


#endif // _PLAYER_INCLUDE


