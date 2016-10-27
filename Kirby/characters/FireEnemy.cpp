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
}


void FireEnemy::update(int deltaTime){

    //if (isInFrustrum()) {
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
	mScene->collisionMoveDown(this); //if it's at floor, will undo previous increment, otherwise will fall

    BaseEnemy::update(deltaTime);
    //}
}
