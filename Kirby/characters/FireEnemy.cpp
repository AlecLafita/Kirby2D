//
// Created by quokka on 26/10/16.
//

#include "FireEnemy.h"
#include "../base/Scene.h"


FireEnemy::FireEnemy()
{
    dir = glm::ivec2(-1, 0);

    Character::setPathToSpriteSheet("images/firy_enemy_spritesheet.png");

    mNumberAnimations = 8;

    mSpriteRows = 6;

    mNumStand = 2;
    mNumMove = 4;
    mNumAttack = 2;
    mNumFly = 0;

    //Sprite rows
    START_ROW_STAND_RIGHT = 0;
    START_ROW_STAND_LEFT = 1;
    START_ROW_MOVE_RIGHT = 2;
    START_ROW_MOVE_LEFT = 3;
    START_ROW_ATTACK_RIGHT = 4;
    START_ROW_ATTACK_LEFT = 5;
}


void FireEnemy::init(ShaderProgram &shaderProgram, Scene *scene){

    WalkingDummyEnemy::init(shaderProgram, scene);
    sprite->changeAnimation(MOVE_LEFT);
	mFire = new BigObject();
	//mFire->setPathToSpriteSheet(OBJECTS_SPRITESHEET_PATH); //OBJECT SPRITESHEET
	//mFire->setTexturePosition(glm::fvec2(0.25f, 0.25f)); //POSITION IN SPRITESHEET
	mFire->init(shaderProgram, scene);

}


void FireEnemy::update(int deltaTime){

    //if (isInFrustrum()) {

	if (isAttacking) {
		//Maybe stop attacking
		int ran = rand() % 3000;
		if (ran > 1000 && ran < 1050) {// stop
			if (dir.x > 0) sprite->changeAnimation(STAND_RIGHT);
			else sprite->changeAnimation(STAND_LEFT);
			isAttacking = false;
			mFire->setPosition(glm::ivec2(-100, -100));//Set object to invalid position in order to not collide
		}
		else { //continue attacking
			BaseEnemy::update(deltaTime);
			mFire->update(deltaTime);
			return;
		}
	}
	searchPlayer();

	//Move to corresponding direction
	posCharacter += dir;
	if (dir.x < 0) { //Go left
		if (mScene->collisionMoveLeft(this)) {
			sprite->changeAnimation(MOVE_RIGHT);
			posCharacter -= dir;
			dir = -dir;
		}
	}
	else { //Go right
		if (mScene->collisionMoveRight(this)) {
			sprite->changeAnimation(MOVE_LEFT);
			posCharacter -= dir;
			dir = -dir;
		}
	}

	posCharacter.y += FALL_STEP;//going down
	bool atGround = mScene->collisionMoveDown(this); //if it's at floor, will undo previous increment, otherwise will fall
	if (!isAttacking && atGround) {
		int ran = rand() % 3000;
		if (ran > 2000 && ran < 2030) {// start attacking
			if (dir.x > 0)  {
				sprite->changeAnimation(ATTACK_RIGHT);
				mFire->setPosition(glm::ivec2(posCharacter.x + getSize().x, posCharacter.y));
			}
			else {
				sprite->changeAnimation(ATTACK_LEFT);
				mFire->setPosition(glm::ivec2(posCharacter.x - BIG_OBJECT_SIZE_X, posCharacter.y));
			}
			isAttacking = true;
		}
	}
    BaseEnemy::update(deltaTime);
    //}
}

void FireEnemy::render() {
	BaseEnemy::render();
	if (isAttacking) mFire->render();
}