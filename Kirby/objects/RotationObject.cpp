#include "RotationObject.h"

#include "../base/Scene.h"

#include <glm/gtc/matrix_transform.hpp>


RotationObject::RotationObject()
{
	mNumberAnimations = 1;
	START_ROW_RIGHT = 0;

	angleIncr = 0.0f;
}

void RotationObject::init(ShaderProgram &shaderProgram, Scene* scene) {
	mScene = scene;

	int mSpriteColumns = 1;
	int mSpriteRows = 1;

	float columnSize = 1.f / float(mSpriteColumns);
	float rowSize = 1.f / float(mSpriteRows);

	spritesheet.loadFromFile(mPathToSpritesheet, TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(24, 7), glm::vec2(columnSize, rowSize), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(mNumberAnimations);
	sprite->setAnimationSpeed(LEFT, 8);

	for (int i = 0; i < mSpriteColumns; ++i) {
		sprite->addKeyframe(LEFT, glm::vec2(i*columnSize, START_ROW_LEFT*rowSize));
	}

	sprite->changeAnimation(0);
}

void RotationObject::update(int deltaTime) {
	//posObj += dir;
	//glm::vec4 newPos = glm::vec4(posObj.x,posObj.y,0,0);
	angleIncr += 0.1f;
	glm::mat4 transform;
	transform = glm::rotate(transform,angleIncr,glm::vec3(0,0,1));
	transform = glm::translate(transform,glm::vec3(posObj.x,posObj.y,0));
	posObj = glm::ivec2(transform[3][0],transform[3][1]);
	BaseObject::update(deltaTime);
}

