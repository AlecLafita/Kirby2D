#include "FireKirby.h"
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

void FireKirby::update(int deltaTime) {
	cout << "fire" << endl;
	Player::update(deltaTime);
}

