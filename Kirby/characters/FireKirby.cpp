#include "FireKirby.h"
#include "../base/Game.h"

#include <iostream>
using namespace std;

FireKirby::FireKirby()
{
	setPathToSpriteSheet("images/fire_kirby_spritesheet.png");
	mSpriteRows = 10;

	//mSpriteRows = 11;
	mNumberAnimations = 10;

	mNumDeath = 8;
	mNumFly = 6;
	mNumSwallow = 2;
}

void FireKirby::init(ShaderProgram &shaderProgram, Scene* scene) {
	Player::init(shaderProgram, scene);
	//Creae fire object
	mFire = new BigObject();
	//mFire->setPathToSpriteSheet(OBJECTS_SPRITESHEET_PATH); //OBJECT SPRITESHEET
	//mFire->setTexturePosition(glm::fvec2(0.25f, 0.25f)); //POSITION IN SPRITESHEET
	mFire->init(shaderProgram, scene);
}

void FireKirby::update(int deltaTime) {
	Player::update(deltaTime);
	if (bAttacking && Game::instance().getKey('a')) {
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
		if (isLeftDirection()) mFire->setLeftAnimation();
		else mFire->setRightAnimation(); 
	}
}

void FireKirby::render() {
	Player::render();
	if (bAttacking && Game::instance().getKey('a'))
		mFire->render();
}


int FireKirby::getAttackSound() {
	return SOUND_FIRE;
}