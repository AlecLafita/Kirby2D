#include "BigObject.h"
#include <iostream>
#include "../base/Defines.h"

BigObject::BigObject()
{

	mNumberAnimations = 2;
	//setPathToSpriteSheet(BIG_OBJECTS_SPRITESHEET_PATH);
	bTaken = false;

	START_ROW_LEFT = 0;
	START_ROW_RIGHT = 0;
}



void BigObject::init(ShaderProgram &shaderProgram, Scene* scene) {
	mScene = scene;

	int mSpriteColumns = 10;
	int mSpriteRows = 1;

	float columnSize = 1.f / float(mSpriteColumns);
	float rowSize = 1.f / float(mSpriteRows);

	spritesheet.loadFromFile(mPathToSpritesheet, TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(BIG_OBJECT_SIZE_X, BIG_OBJECT_SIZE_Y), glm::vec2(columnSize, rowSize), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(mNumberAnimations);
	sprite->setAnimationSpeed(LEFT, 8);
	sprite->setAnimationSpeed(RIGHT, 8);

	for (int i = 0; i < mSpriteColumns; ++i) {
		sprite->addKeyframe(LEFT, glm::vec2(i*columnSize, START_ROW_LEFT*rowSize));
		sprite->addKeyframe(RIGHT, glm::vec2(i*columnSize, START_ROW_RIGHT*rowSize));
	}

	sprite->changeAnimation(0);
}