#include "PortalObject.h"
#include <iostream>
#include "../base/Defines.h"
#include "../base/Scene.h"

PortalObject::PortalObject(int type)
{
	this->type = type;
	mNumberAnimations = 1;
	setPathToSpriteSheet(BIG_OBJECTS_FIRE_PATH);
	bTaken = false;
	//START_ROW_LEFT = 0;
	//START_ROW_RIGHT = 0;
}



void PortalObject::init(ShaderProgram &shaderProgram, Scene* scene) {
	mScene = scene;

	int mSpriteColumns = 10;
	int mSpriteRows = 1;

	float columnSize = 1.f / float(mSpriteColumns);
	float rowSize = 1.f / float(mSpriteRows);

	spritesheet.loadFromFile(mPathToSpritesheet, TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(BIG_OBJECT_SIZE_X, BIG_OBJECT_SIZE_Y), glm::vec2(columnSize, rowSize), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(mNumberAnimations);
	/*sprite->setAnimationSpeed(LEFT, 8);
	sprite->setAnimationSpeed(RIGHT, 8);

	for (int i = 0; i < mSpriteColumns; ++i) {
		sprite->addKeyframe(LEFT, glm::vec2(i*columnSize, START_ROW_LEFT*rowSize));
		sprite->addKeyframe(RIGHT, glm::vec2(i*columnSize, START_ROW_RIGHT*rowSize));
	}*/
	sprite->setAnimationSpeed(0,8);
	sprite->addKeyframe(0, glm::vec2(0,0));
	sprite->changeAnimation(0);
}

void PortalObject::update(int deltaTime) {
	//if(isInfrustrum())
	mScene->characterTakesPortal(this);
	BaseObject::update(deltaTime);
}