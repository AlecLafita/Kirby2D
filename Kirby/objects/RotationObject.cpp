#include "RotationObject.h"

#include "../base/Scene.h"

#include <glm/gtc/matrix_transform.hpp>


RotationObject::RotationObject()
{
	mNumberAnimations = 1;
	START_ROW_RIGHT = 0;

	angleIncr = 0.0f;

	START_ROW_LEFT = 0;
}

void RotationObject::init(ShaderProgram &shaderProgram, Scene* scene) {
	mScene = scene;

	int mSpriteColumns = 5;
	int mSpriteRows = 4;

	float columnSize = 1.f / float(mSpriteColumns);
	float rowSize = 1.f / float(mSpriteRows);

	spritesheet.loadFromFile(mPathToSpritesheet, TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(BIG_OBJECT_SIZE_X, BIG_OBJECT_SIZE_Y), glm::vec2(columnSize, rowSize), &spritesheet, &shaderProgram);
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
	angleIncr += 0.2f;
	glm::mat4 transform;
	transform = glm::translate(transform,glm::vec3(centralPosChar.x-radiusChar/2,centralPosChar.y-radiusChar/2,0));
	transform = glm::rotate(transform,angleIncr*dirRot,glm::vec3(0,0,1));
	transform = glm::translate(transform,glm::vec3(radiusChar,0,0));
	posObj = glm::ivec2(transform[3][0],transform[3][1]);
	BaseObject::update(deltaTime);
}

