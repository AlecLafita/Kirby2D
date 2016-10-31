#include "FireKirby.h"
#include "../base/Game.h"

#include <iostream>
using namespace std;

FireKirby::FireKirby()
{
	setPathToSpriteSheet("images/fire_kirby_spritesheet.png");
	mSpriteRows = 10;

	//mSpriteRows = 11;
	mNumberAnimations = 9;

	mAttackSoundTime = 1300;
	mNumDeath = 7;
	mNumFly = 6;
	mNumSwallow = 2;

	START_ROW_DEATH = 9;
}

void FireKirby::init(ShaderProgram &shaderProgram, Scene* scene) {
	Player::init(shaderProgram, scene);
	//Creae fire object
	mFire = new BigObject();
	mFire->setPathToSpriteSheet(BIG_OBJECTS_FIRE_PATH); //OBJECT SPRITESHEET
	mFire->init(shaderProgram, scene);
}

void FireKirby::update(int deltaTime) {
	Player::update(deltaTime);
	if (bAttacking && (Game::instance().getKey('a') || Game::instance().getKey('A'))) {
		if (isLeftDirection()) {
			mFire->setPosition(glm::ivec2(posCharacter.x - BIG_OBJECT_SIZE_X, posCharacter.y));
			mFire->update(deltaTime);
		}
		else {
			mFire->setPosition(glm::ivec2(posCharacter.x + getSize().x, posCharacter.y));
			mFire->update(deltaTime);
		}
	}
	else {
		mFire->setPosition(glm::ivec2(-100, -100));//Set object to invalid position in order to not collide
		if (isLeftDirection()) mFire->setLeftAnimation();
		else mFire->setRightAnimation(); 
	}
}

void FireKirby::render() {
	Player::render();
	if (bAttacking && (Game::instance().getKey('a')) || Game::instance().getKey('A'))
		mFire->render();
}


int FireKirby::getAttackSound() {
	return SOUND_FIRE;
}