//
// Created by quokka on 12/10/16.
//

#include "PinxoEnemy.h"
#include "../base/Scene.h"

PinxoEnemy::PinxoEnemy(){

    Character::setPathToSpriteSheet("images/pinxos_spritesheet.png");
    mSpriteRows = 1;

    mNumStand = 2;
    mNumMove = 2;
    mNumAttack = 0;

    //Sprite rows
    START_ROW_STAND_RIGHT = 0;
    START_ROW_STAND_LEFT = 0;
    START_ROW_MOVE_RIGHT = 0;
    START_ROW_MOVE_LEFT = 0;

	dir = glm::ivec2(0,1);

	isSwallable = false;
}

PinxoEnemy::~PinxoEnemy(){

}

void PinxoEnemy::init(ShaderProgram &shaderProgram,Scene *scene){

    Character::init(shaderProgram, scene);
}


void PinxoEnemy::update(int deltaTime){

    //if (isInFrustrum()){
		posCharacter += dir;
		if (dir.y < 0) { //Go top
			if (mScene->collisionMoveUp(this)) {
				posCharacter -= dir;
				dir = -dir;
			}
		}
		else { //Go botttom
			if (mScene->collisionMoveDown(this)) {
				posCharacter -= dir;
				dir = -dir;
			}
		}
        BaseEnemy::update(deltaTime);
    //}
}
