#include <iostream>
#include "BaseEnemy.h"
using namespace std;
#include "../base/Scene.h"


BaseEnemy::BaseEnemy(){
	int en = rand() % 3; //number of enemies
	cout << en << endl;
	switch (en) {
	case 0:
		Character::setPathToSpriteSheet("images/chicken_enemy_spritesheet.png");
		break;
	case 1:
		Character::setPathToSpriteSheet("images/ugly_enemy_spritesheet.png");
		break;

    case 2:
			Character::setPathToSpriteSheet("images/bird_enemy_spritesheet.png");
    break;
		default:
		break;
	}

	mNumberAnimations = 8;

	mSpriteRows = 6;

	mNumStand = 2;
	mNumMove = 3;
	mNumAttack = 0;
	mNumFly = 3;

	//Sprite rows

	START_ROW_MOVE_RIGHT = 0;
	START_ROW_MOVE_LEFT = 1;
	START_ROW_FLY_RIGHT = 2;
	START_ROW_FLY_LEFT= 3;

	dir = glm::ivec2(0, 0);
}


BaseEnemy::~BaseEnemy() {
}


void BaseEnemy::init(ShaderProgram &shaderProgram,Scene* scene){

	Character::init(shaderProgram,scene);

}

void BaseEnemy::update(int deltaTime){

	if (isInFrustrum()){
		if (isSwallable) {
			if (mScene->playerCanKill(this))
				isDead = true;
		}
	}
	Character::update(deltaTime);

}

bool BaseEnemy::isInFrustrum(){
	int cameraLeft = mScene->getCameraLeftPosition();
	return ((posCharacter.x + CHARACTER_SIZE_X)>cameraLeft && posCharacter.x<(cameraLeft + SCREEN_WIDTH-1));
}