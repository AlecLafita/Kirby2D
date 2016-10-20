#include "BaseObject.h"
#include <iostream>
#include "../base/Defines.h"

BaseObject::BaseObject() {
	mNumberAnimations = 1;
}

void BaseObject::init(ShaderProgram &shaderProgram, Scene* scene) {
	mScene = scene;
	spritesheet.loadFromFile(OBJECTS_SPRITESHEET_PATH, TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.25, 0.25), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(mNumberAnimations);
		sprite->setAnimationSpeed(0, 8);
		sprite->addKeyframe(0, glm::vec2(mTexturePosition.x, mTexturePosition.y));

	sprite->changeAnimation(0);

}

void BaseObject::setTexturePosition(const glm::fvec2 &pos) {
	mTexturePosition = pos;
}

void BaseObject::update(int deltaTime) {
	sprite->update(deltaTime);
	sprite->setPosition(glm::vec2(float(posObj.x), float(posObj.y)));

}

void BaseObject::render() {
	sprite->render();
}


void BaseObject::setPosition(const glm::vec2 &pos)
{
	posObj = pos;
	sprite->setPosition(glm::vec2(float(posObj.x), float(posObj.y)));
}