#pragma once
#include "Character.h"
class Player : public Character
{


public:
	Player();
	~Player();

	virtual void init(ShaderProgram &shaderProgram, Scene* scene);
	virtual void update(int deltaTime);

	void computeNextMove(int deltaTime);
	void computeJumping();
	void computeAnimation(int deltaTime);

	bool isSwalling() const { return bAttacking; }
	void justDamaged(); //trigered when character has been damaged
	void recoverEnergy (int energyToRecover); //triggered when gathered an item 

	int getEnergy() { return energy; }
	void setEnergy (int newEnergy) { energy = newEnergy; }

    bool isBeingAnimated(){
        return bAnimating;
    }

	void playTransformationSound();
    bool isReadyToTransform() { return bReadyToTransform; }
    bool isFacingLeftSide(); //Redundancy with this and Character's is lookingLeft!
    bool isFacingRightSide();

protected:
	virtual void computeAttack(int deltaTime);
	virtual void computeMovement();
	virtual void computeJump();
	virtual int getAttackSound(){ return SOUND_VACUUMING; }

protected:
    int mAttackSoundTime;

private:
	bool bHoving;
	int nJumps;

	bool bAnimating, bReadyToTransform;

	int energy;

	int mNumEatStandRight, mNumEatStandLeft;
	int mNumEatMoveRight, mNumEatMoveLeft;
	int mFlyRight, mFlyLeft;

	int mAnimationTime, mAttackTime;

	//Constants
	int START_ROW_EAT_STAND_RIGHT;
	int START_ROW_EAT_STAND_LEFT;
	int START_ROW_EAT_MOVE_RIGHT;
	int START_ROW_EAT_MOVE_LEFT;
	int START_ROW_FLY_RIGHT;
	int START_ROW_FLY_LEFT;

};

