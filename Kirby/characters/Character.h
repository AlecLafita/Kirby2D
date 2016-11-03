#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE

#include "../base/Sprite.h"
#include "../base/Defines.h"


// Character respresent any general character(player or enemy). Abstract class

enum BasicPlayerAnims //even -> left, odd ->right
{
	STAND_LEFT, STAND_RIGHT,
	MOVE_LEFT, MOVE_RIGHT,
	ATTACK_LEFT, ATTACK_RIGHT,
	FLY_LEFT, FLY_RIGHT,
	//SWALLOW_LEFT, SWALLOW_RIGHT,
	DEATH
};

class Scene;


class Character
{

public:
	Character();
	~Character(){}

	void init(ShaderProgram &shaderProgram,Scene* scene);
	void update(int deltaTime);
	virtual void render();
	
	void setPathToSpriteSheet(string pathToSpriteSheet); //must be called before init
	void setPosition (const glm::vec2 &pos);
	glm::ivec2 getPosition() const { return posCharacter; }
	glm::ivec2 getSize() const { return glm::ivec2(CHARACTER_SIZE_X, CHARACTER_SIZE_Y); }
	void setPosition(glm::ivec2 pos) { posCharacter = pos; }
	bool isCharacterDead() const{ return isDead; }

	virtual glm::ivec2 getCollisionPosition() const { return getPosition() +glm::ivec2(6,10);}
	virtual glm::ivec2 getCollisionSize() const {return getSize() -glm::ivec2(12,12);}

	//Redundancy with this and Player's isleftDireciton!
	bool isLeftDirection() const { return (sprite->animation() % 2) == 0; } //is character loocking to left?

	virtual void justDamaged(bool enemyOnLeft); //trigered when character has been damaged

	virtual void getType() {}

	void setStartAnimation(int animId){ mStartAnimation = animId;}
	int getStartAnimation(){ return mStartAnimation;}

	int getNoPortal() {return noPortal;}
	void setNoPortal(int nop) {noPortal = nop;}
	void setStartY(int newstartY) {startY = newstartY;}
	int getStartY() {return startY;}

protected:

	int mStartAnimation;
	bool bJumping, bAttacking;
	glm::ivec2 posCharacter;
	int jumpAngle, startY;
	string mPathToSpritesheet;
	Texture spritesheet;
	Sprite *sprite;
	Scene* mScene;
	int mNumberAnimations, mSpriteColumns, mSpriteRows;
    int mNumStand; // Number of stand left/right sprites
    int mNumMove; // Number of move left/right sprites
    int mNumAttack; // Number of attack left/right sprites
    int mNumFly; // Number of fly left/right sprites
    int mNumSwallow; // Number of swallow left/right sprites
    int mNumDeath; // Number of swallow left/right sprites

	bool isSwallable; //indicates if Kirby can swallow this character -> if is false, colliding with this enemy will damage Kirby
	bool isDead;//Ready to be deleted

	int framesDamaged; //Frames needed for the character to sopt being damaged(can not get more damage until it's 0)
	glm::ivec2 directionDamaged; //Direction to send character when being damaged

	int noPortal;//Frames until can use another portal

    // Constants
    int START_ROW_STAND_RIGHT;
    int START_ROW_STAND_LEFT;
    int START_ROW_MOVE_RIGHT;
    int START_ROW_MOVE_LEFT;
    int START_ROW_ATTACK_RIGHT;
    int START_ROW_ATTACK_LEFT;
    int START_ROW_FLY_LEFT;
    int START_ROW_FLY_RIGHT;
	int START_ROW_SWALLOW_LEFT;
    int START_ROW_SWALLOW_RIGHT;
    int START_ROW_DEATH;
};


#endif // _PLAYER_INCLUDE


