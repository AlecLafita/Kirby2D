#pragma once
#include "Character.h"
class Player : public Character
{


public:
	Player();
	~Player();

	void computeNextMove();
	void computeJumping();
	void init(ShaderProgram &shaderProgram, Scene* scene);
	void update(int deltaTime);

	bool isSwalling() const { return bAttacking; }
	void justDamaged(); //trigered when character has been damaged

	void getType() {}

private:
	bool bHoving;
	int nJumps;

	int energy, lifes;

	int mNumEatStandRight, mNumEatStandLeft;
	int mNumEatMoveRight, mNumEatMoveLeft;
	int mFlyRight, mFlyLeft;

	//Constants
	int START_ROW_EAT_STAND_RIGHT;
	int START_ROW_EAT_STAND_LEFT;
	int START_ROW_EAT_MOVE_RIGHT;
	int START_ROW_EAT_MOVE_LEFT;
	int START_ROW_FLY_RIGHT;
	int START_ROW_FLY_LEFT;

};

