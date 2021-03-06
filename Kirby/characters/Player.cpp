#include "Player.h"
#include <GL/glut.h>
#include "../base/Game.h"

#include <iostream>
using namespace std;

Player::Player() {
    bAnimating = false;
	mSpriteRows = 6;
	mNumberAnimations = 6;

    mNumSwallow = 2;
}


void Player::init(ShaderProgram &shaderProgram, Scene *scene){
	
	Character::init(shaderProgram,scene);
    mAttackSoundTime = 2300;
	bHoving = false;
	nJumps = 0;
	energy = MAX_ENERGY;
    bReadyToTransform = false;
	isSwallable = false; //Kirby can't swallow itself (this may not be necesary for the game logic)

}

void Player::update(int deltaTime){
    if(!bAnimating){

        computeNextMove(deltaTime);
    } else {

        computeAnimation(deltaTime);
    }
	Character::update(deltaTime);
}


void Player::computeNextMove(int deltaTime) {
	computeAttack(deltaTime);
	computeMovement();
	computeJump();
}

void Player::computeAttack(int deltaTime){
	// ---- ATTACK ----
	//Attacking block, only for Kirby(no abilities)
	if (Game::instance().getKey('a') || Game::instance().getKey('A')) { //attack (swallow)
		if (!bAttacking){
			mAttackTime = 0;
			Game::instance().playSound(getAttackSound());

			if (isFacingLeftSide()){
				sprite->changeAnimation(ATTACK_LEFT);
				bAttacking = true;
			}
			else if (isFacingRightSide()){
				sprite->changeAnimation(ATTACK_RIGHT);
				bAttacking = true;
			}
		} else {

			mAttackTime += deltaTime;
			if(mAttackTime > mAttackSoundTime){

				if (isFacingLeftSide()){
					sprite->changeAnimation(STAND_LEFT);
				}
				else {
					sprite->changeAnimation(STAND_RIGHT);
				}
			}
		}

		/*if (sprite->animation() != ATTACK_LEFT && sprite->animation() != ATTACK_RIGHT) { //a pressed but moving
			Game::instance().stopSound(getAttackSound());
			bAttacking = false;
		}*/
		//return;
	}
	else {
		Game::instance().stopSound(getAttackSound());
		bAttacking = false;
		if (sprite->animation() == ATTACK_LEFT)
			sprite->changeAnimation(STAND_LEFT);
		else if (sprite->animation() == ATTACK_RIGHT)
			sprite->changeAnimation(STAND_RIGHT);
	}

}

void Player::computeMovement() {
	if (bAttacking) return;

	// ---- LEFT / RIGHT----
	if (Game::instance().getSpecialKey(GLUT_KEY_LEFT)) {

		if (bJumping && sprite->animation() != FLY_LEFT){

			sprite->changeAnimation(FLY_LEFT);
		}
		else if (!bJumping && sprite->animation() != MOVE_LEFT){

			sprite->changeAnimation(MOVE_LEFT);
		}
		posCharacter.x -= MOVEMENT_DEFAULT;
		if (mScene->collisionMoveLeft(this)) {
			posCharacter.x += MOVEMENT_DEFAULT;
			if (!bJumping){

				sprite->changeAnimation(STAND_LEFT);
			}
		}
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT)){

		if (bJumping && sprite->animation() != FLY_RIGHT){

			sprite->changeAnimation(FLY_RIGHT);
		}
		else if (!bJumping && sprite->animation() != MOVE_RIGHT){

			sprite->changeAnimation(MOVE_RIGHT);
		}
		posCharacter.x += MOVEMENT_DEFAULT;
		if (mScene->collisionMoveRight(this)) {
			posCharacter.x -= MOVEMENT_DEFAULT;
			if (!bJumping){

				sprite->changeAnimation(STAND_RIGHT);
			}
		}
	}
	else {
		//Stops walking.
		if (sprite->animation() == MOVE_LEFT)
			sprite->changeAnimation(STAND_LEFT);
		else if (sprite->animation() == MOVE_RIGHT)
			sprite->changeAnimation(STAND_RIGHT);
	}
}

void Player::computeJump() {

	if (bJumping) {//Player at the air
		jumpAngle += JUMP_ANGLE_STEP;
		if (mScene->collisionMoveDown(this) || jumpAngle == ANGLE_GROUND) { //Very near the ground
			bJumping = false;
			bHoving = false;
			//posCharacter.y = startY;
		}
		else {//going up when 0<=jumpAngle<=90, down when 90<jumpAngle<=180
			posCharacter.y = int(startY - JUMP_HEIGHT * sin(3.14159f * jumpAngle / 180.f));
			if (mScene->collisionMoveUp(this)) {
				posCharacter.y = int(startY - JUMP_HEIGHT * sin(3.14159f * (jumpAngle - JUMP_ANGLE_STEP) / 180.f));//Undo movement
				bJumping = false;
				bHoving = true;
			}
			else if (jumpAngle > 90) { //starting to go down, from this point the sinus function will be decreasing
				bJumping = !mScene->collisionMoveDown(this);
				bHoving = true;
			}
		}
	}
	else {
		posCharacter.y += FALL_STEP;//going down
		if (mScene->collisionMoveDown(this)) { //at floor
			bHoving = false;
			if (Game::instance().getSpecialKey(GLUT_KEY_UP)) {
				nJumps = 0;
				computeJumping();
			}
		}
	}

	if (bHoving && Game::instance().getSpecialKey(GLUT_KEY_UP) && nJumps < MAX_JUMPS) {
		computeJumping();
	}
}

void Player::computeAnimation(int deltaTime) {

    if(isDead){

        if(sprite->animation() != DEATH){
            sprite->changeAnimation(DEATH);
        }
        mAnimationTime += deltaTime;
        if(mAnimationTime > 2500){       // A little over 2.5secs (in millis)

            bAnimating = false; // Stop animation.
            mAnimationTime = 0;
        }
    }
}

void Player::justDamaged(bool enemyOnLeft) {
	if (framesDamaged == 0) {

        if(energy > 0){

            energy--;
        }
	
		Game::instance().setPlayerEnergy(energy);
		Game::instance().playSound(SOUND_DAMAGE);
		if(energy == 0){

			Game::instance().stopMusic();
			Game::instance().playSound(SOUND_DEATH);
            mScene->setSceneToReset();
            bAnimating = true;
            isDead = true;
            mAnimationTime = 0;
			return;
        }
	}
	Character::justDamaged(enemyOnLeft);
}

void Player::recoverEnergy(int energyToRecover) {
	energy += energyToRecover;
	energy = min(energy, MAX_ENERGY);
	Game::instance().setPlayerEnergy(energy);
	Game::instance().playSound(SOUND_GET_ENERGY);

}

void Player::computeJumping(){

	if (!bAttacking) {
		if (isFacingLeftSide()){
			sprite->changeAnimation(FLY_LEFT);
		}
		else {
			sprite->changeAnimation(FLY_RIGHT);
		}
		Game::instance().playSound(SOUND_JUMPING);
		nJumps++;
		bHoving = false;
		bJumping = true;
		jumpAngle = 0;
		startY = posCharacter.y;
	}
}

bool Player::isFacingLeftSide() {

    return sprite->animation() == ATTACK_LEFT ||
           sprite->animation() == FLY_LEFT ||
           sprite->animation() == STAND_LEFT ||
           sprite->animation() == MOVE_LEFT;
}

bool Player::isFacingRightSide() {
    return sprite->animation() == ATTACK_RIGHT ||
           sprite->animation() == FLY_RIGHT ||
           sprite->animation() == STAND_RIGHT ||
		   sprite->animation() == MOVE_RIGHT;
}


void Player::playTransformationSound() {

	Game::instance().playSound(SOUND_TRANSFORMATION);
}
Player::~Player()
{
}
