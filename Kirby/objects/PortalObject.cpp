#include "PortalObject.h"
#include <iostream>
#include "../base/Defines.h"
#include "../base/Scene.h"

PortalObject::PortalObject(int type, int index)
{
	this->type = type;
	this->index	= index;
	mNumberAnimations = 1;
	setPathToSpriteSheet(PORTAL_OBJECT_PATH);
	bTaken = false;
}



void PortalObject::init(ShaderProgram &shaderProgram, Scene* scene) {
	mScene = scene;

	int mSpriteColumns = 1;
	int mSpriteRows = 2;

	float columnSize = 1.f / float(mSpriteColumns);
	float rowSize = 1.f / float(mSpriteRows);

	spritesheet.loadFromFile(mPathToSpritesheet, TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(OBJECT_SIZE_X, BIG_OBJECT_SIZE_Y), glm::vec2(columnSize, rowSize), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(mNumberAnimations);
	sprite->setAnimationSpeed(0,8);
	if (type) sprite->addKeyframe(0, glm::vec2(0,0));
	else sprite->addKeyframe(0, glm::vec2(0,rowSize));
	sprite->changeAnimation(0);
}

void PortalObject::update(int deltaTime) {
	//if(isInfrustrum())
	mScene->elementTakesPortal(this);
	BaseObject::update(deltaTime);
}