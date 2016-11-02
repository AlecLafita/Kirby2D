#include "ProjectileObject.h"

#include <iostream>
using namespace std;

ProjectileObject::ProjectileObject()
{
	mNumberAnimations = 2;
	START_ROW_LEFT = 0;
	START_ROW_RIGHT = 0;
}

void ProjectileObject::init(ShaderProgram &shaderProgram, Scene* scene) {
	mScene = scene;

	int mSpriteColumns = 1;
	int mSpriteRows = 2;

	float columnSize = 1.f / float(mSpriteColumns);
	float rowSize = 1.f / float(mSpriteRows);

	spritesheet.loadFromFile(mPathToSpritesheet, TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(24, 7), glm::vec2(columnSize, rowSize), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(mNumberAnimations);
	sprite->setAnimationSpeed(LEFT, 8);
	sprite->setAnimationSpeed(RIGHT, 8);

	for (int i = 0; i < mSpriteColumns; ++i) {
		sprite->addKeyframe(LEFT, glm::vec2(i*columnSize, START_ROW_LEFT*rowSize));
		sprite->addKeyframe(RIGHT, glm::vec2(i*columnSize, START_ROW_RIGHT*rowSize));
	}

	sprite->changeAnimation(0);
}

void ProjectileObject::update(int deltaTime) {
	posObj += dir;
	//TODO COLLISIONS
	BaseObject::update(deltaTime);
}

void ProjectileObject::setDirection(glm::fvec2 dir) {
	this->dir = dir;
}
