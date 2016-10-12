#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include "Character.h"
#include "Game.h"


Character::Character(){

	mNumberAnimations = 4;
    mSpriteColumns = 10;
    mSpriteRows = 6;

    //Default
    mNumStandLeft = 3;
    mNumStandRight = 3;
    mNumMoveLeft = 10;
    mNumMoveRight = 10;
    mNumAttackLeft = 3;
    mNumAttackRight = 3;
}

void Character::init(ShaderProgram &shaderProgram)
{
	bJumping = false;

    float columnSize = float(1)/float(mSpriteColumns);
    float rowSize = float(1)/float(mSpriteRows);
    cout << columnSize << endl;

	spritesheet.loadFromFile(mPathToSpritesheet, TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(columnSize, rowSize), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(mNumberAnimations);
	
		sprite->setAnimationSpeed(STAND_LEFT, 8);
        for (int i = 0; i < mNumStandLeft; ++i) {
            sprite->addKeyframe(STAND_LEFT, glm::vec2(i*columnSize, START_ROW_STAND_LEFT*rowSize));
        }

		sprite->setAnimationSpeed(STAND_RIGHT, 8);
        for (int i = 0; i < mNumStandRight; ++i) {
            sprite->addKeyframe(STAND_RIGHT, glm::vec2(i*columnSize, START_ROW_STAND_RIGHT*rowSize));
        }

		sprite->setAnimationSpeed(MOVE_LEFT, 8);
        for (int i = 0; i < mNumMoveLeft; ++i) {
            sprite->addKeyframe(MOVE_LEFT, glm::vec2(i*columnSize, START_ROW_MOVE_LEFT*rowSize));
        }

		sprite->setAnimationSpeed(MOVE_RIGHT, 8);
        for (int i = 0; i < mNumMoveLeft; ++i) {
            sprite->addKeyframe(MOVE_RIGHT, glm::vec2(i*columnSize, START_ROW_MOVE_RIGHT*rowSize));
        }

	sprite->changeAnimation(1);
	sprite->setPosition(glm::vec2(float(posCharacter.x), float(posCharacter.y)));
	
}

void Character::setPathToSpriteSheet(string path){

	mPathToSpritesheet = path;
}

void Character::update(int deltaTime)
{
	sprite->update(deltaTime);
	sprite->setPosition(glm::vec2(float(posCharacter.x), float(posCharacter.y)));
}

void Character::render()
{
	sprite->render();
}

void Character::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Character::setPosition(const glm::vec2 &pos)
{
	posCharacter = pos;
	sprite->setPosition(glm::vec2(float(posCharacter.x), float(posCharacter.y)));
}

glm::vec2 Character::getPosition() {
	return glm::vec2(float(posCharacter.x), float(posCharacter.y));
}




