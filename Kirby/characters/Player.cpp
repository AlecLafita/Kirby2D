#include "Player.h"
#include <GL/glut.h>
#include "../base/Game.h"

#include <iostream>
using namespace std;

Player::Player()
{
	mSpriteRows = 10;
	mNumberAnimations = 6;
}

void Player::init(ShaderProgram &shaderProgram, Scene *scene){
	
	Character::init(shaderProgram,scene);
	bHoving = false;
	nJumps = 0;
	energy = MAX_ENERGY;
	isSwallable = false; //Kirby can't swallow itself (this may not be necesary for the game logic)

}

void Player::update(int deltaTime){

	computeNextMove();
	Character::update(deltaTime);
}


void Player::computeNextMove() {

	//Attacking block, only for Kirby(no abilities)
	if (Game::instance().getKey('a')) { //attack (swallow)
		if (!bAttacking){

			Game::instance().playSound(SOUND_VACUUMING);

			if (sprite->animation() == STAND_LEFT){
				sprite->changeAnimation(ATTACK_LEFT);
				bAttacking = true;
			}
			else if (sprite->animation() == STAND_RIGHT){
				sprite->changeAnimation(ATTACK_RIGHT);
				bAttacking = true;
			}
		}

		if (sprite->animation() != ATTACK_LEFT && sprite->animation() != ATTACK_RIGHT) { //a pressed but moving
			Game::instance().stopSound(SOUND_VACUUMING);
			bAttacking = false;
		}
	} else {
		Game::instance().stopSound(SOUND_VACUUMING);
		bAttacking = false;
		if (sprite->animation() == ATTACK_LEFT)
			sprite->changeAnimation(STAND_LEFT);
		else if (sprite->animation() == ATTACK_RIGHT)
			sprite->changeAnimation(STAND_RIGHT);
	}


	//Moving rigth/left (keyboard input) block (common for all kirbys)
	if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{
		if (sprite->animation() != MOVE_LEFT)
			sprite->changeAnimation(MOVE_LEFT);
		posCharacter.x -= MOVEMENT_DEFAULT;
		if (mScene->collisionMoveLeft(this))
		{
			posCharacter.x += MOVEMENT_DEFAULT;
			sprite->changeAnimation(STAND_LEFT);
		}
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{
		if (sprite->animation() != MOVE_RIGHT)
			sprite->changeAnimation(MOVE_RIGHT);
		posCharacter.x += MOVEMENT_DEFAULT;
		if (mScene->collisionMoveRight(this))
		{
			posCharacter.x -= MOVEMENT_DEFAULT;
			sprite->changeAnimation(STAND_RIGHT);
		}
	}
	else {
		if (sprite->animation() == MOVE_LEFT)
			sprite->changeAnimation(STAND_LEFT);
		else if (sprite->animation() == MOVE_RIGHT)
			sprite->changeAnimation(STAND_RIGHT);
	}

	//Jumping block (common for all kirbys???)
	if (bJumping) {//Player at the air
		jumpAngle += JUMP_ANGLE_STEP;
		if (jumpAngle == ANGLE_GROUND) { //Very near the ground
			bJumping = false;
			posCharacter.y = startY;
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
			if (Game::instance().getSpecialKey(GLUT_KEY_UP)) {
				nJumps = 0;
				computeJumping();
			}
		}
	}

	if (bHoving && Game::instance().getSpecialKey(GLUT_KEY_UP) && nJumps < MAX_JUMPS) {
       computeJumping();
		//sprite->changeAnimation(HOVING); TODO
	}
}

void Player::justDamaged() {
	if (framesDamaged == 0) {
        if(energy > 0){

            energy--;
        }
        if(energy == 0){

			Game::instance().stopMusic();
			Game::instance().playSound(SOUND_DEATH);
            mScene->setSceneToReset();
			//Do some death animation (?)
			return;
        }
		Game::instance().setPlayerEnergy(energy);
	}
	Character::justDamaged();
}
void Player::computeJumping(){
	Game::instance().playSound(SOUND_JUMPING);
	nJumps++;
	bHoving = false;
	bJumping = true;
	jumpAngle = 0;
	startY = posCharacter.y;
}

Player::~Player()
{
}
