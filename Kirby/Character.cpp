#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include "Character.h"
#include "Game.h"

#define NUM_OF_FRAMES 8
#define NUM_OF_FRAMES_SLOW 5

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

    //Sprite rows
    START_ROW_STAND_RIGHT = 0;
    START_ROW_STAND_LEFT = 1;
    START_ROW_MOVE_RIGHT = 2;
    START_ROW_MOVE_LEFT = 3;
    START_ROW_ATTACK_RIGHT = 4;
    START_ROW_ATTACK_LEFT = 5;
}

void Character::init(ShaderProgram &shaderProgram, Scene* scene)
{
	mScene = scene;

	bJumping = false;

    cout << "START_ROW_STAND_RIGHT  = " << START_ROW_STAND_RIGHT << endl;
    cout << "START_ROW_STAND_LEFT  = " << START_ROW_STAND_LEFT << endl;
    cout << "START_ROW_MOVE_RIGHT  = " << START_ROW_MOVE_RIGHT << endl;
    cout << "START_ROW_MOVE_LEFT  = " << START_ROW_MOVE_LEFT << endl;
    cout << "START_ROW_ATTACK_RIGHT  = " << START_ROW_ATTACK_RIGHT << endl;
    cout << "START_ROW_ATTACK_LEFT  = " << START_ROW_ATTACK_LEFT << endl;


    float columnSize = 1.f/float(mSpriteColumns);
    float rowSize = 1.f/float(mSpriteRows);

	spritesheet.loadFromFile(mPathToSpritesheet, TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(columnSize, rowSize), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(mNumberAnimations);
	
		sprite->setAnimationSpeed(STAND_LEFT, NUM_OF_FRAMES_SLOW);
        for (int i = 0; i < mNumStandLeft; ++i) {
            sprite->addKeyframe(STAND_LEFT, glm::vec2(i*columnSize, START_ROW_STAND_LEFT*rowSize));
        }

		sprite->setAnimationSpeed(STAND_RIGHT, NUM_OF_FRAMES_SLOW);
        for (int i = 0; i < mNumStandRight; ++i) {
            sprite->addKeyframe(STAND_RIGHT, glm::vec2(i*columnSize, START_ROW_STAND_RIGHT*rowSize));
        }

		sprite->setAnimationSpeed(MOVE_LEFT, NUM_OF_FRAMES);
        for (int i = 0; i < mNumMoveLeft; ++i) {
            sprite->addKeyframe(MOVE_LEFT, glm::vec2(i*columnSize, START_ROW_MOVE_LEFT*rowSize));
        }

		sprite->setAnimationSpeed(MOVE_RIGHT, NUM_OF_FRAMES);
        for (int i = 0; i < mNumMoveLeft; ++i) {
            sprite->addKeyframe(MOVE_RIGHT, glm::vec2(i*columnSize, START_ROW_MOVE_RIGHT*rowSize));
        }

		sprite->setAnimationSpeed(ATTACK_RIGHT, NUM_OF_FRAMES);
		for (int i = 0; i < mNumAttackRight; ++i) {
			sprite->addKeyframe(ATTACK_RIGHT, glm::vec2(i*columnSize, START_ROW_ATTACK_RIGHT*rowSize));
		}

		sprite->setAnimationSpeed(ATTACK_LEFT, NUM_OF_FRAMES);
		for (int i = 0; i < mNumAttackLeft; ++i) {
			sprite->addKeyframe(ATTACK_LEFT, glm::vec2(i*columnSize, START_ROW_ATTACK_LEFT*rowSize));
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

void Character::setPosition(const glm::vec2 &pos)
{
	posCharacter = pos;
	sprite->setPosition(glm::vec2(float(posCharacter.x), float(posCharacter.y)));
}





