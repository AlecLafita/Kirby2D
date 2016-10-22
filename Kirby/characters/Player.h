#pragma once
#include "Character.h"
class Player : public Character
{


public:
	Player();
	~Player();

	void init(ShaderProgram &shaderProgram, Scene* scene);
	void update(int deltaTime);

	void computeNextMove();
	void computeJumping();
	void computeAnimation(int deltaTime);

	bool isSwalling() const { return bAttacking; }
	void justDamaged(); //trigered when character has been damaged

	void getType() {}
    bool isBeingAnimated(){
        return bAnimating;
    }

protected:
	bool isFacingLeftSide();
	bool isFacingRightSide();

private:
	bool bHoving;
	int nJumps;

	bool bAnimating;

	int energy;

	int mNumEatStandRight, mNumEatStandLeft;
	int mNumEatMoveRight, mNumEatMoveLeft;
	int mFlyRight, mFlyLeft;

	int mAnimationTime;

	//Constants
	int START_ROW_EAT_STAND_RIGHT;
	int START_ROW_EAT_STAND_LEFT;
	int START_ROW_EAT_MOVE_RIGHT;
	int START_ROW_EAT_MOVE_LEFT;
	int START_ROW_FLY_RIGHT;
	int START_ROW_FLY_LEFT;

};

