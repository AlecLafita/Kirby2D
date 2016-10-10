#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Character.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 70
#define FALL_STEP 4
#define MAX_JUMPS 3

enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT
};


void Character::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	bJumping = false;
	bHoving = false;
	nJumps = 0;
	spritesheet.loadFromFile("images/bub.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.25, 0.25), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(4);
	
		sprite->setAnimationSpeed(STAND_LEFT, 8);
		sprite->addKeyframe(STAND_LEFT, glm::vec2(0.f, 0.f));
		
		sprite->setAnimationSpeed(STAND_RIGHT, 8);
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.25f, 0.f));
		
		sprite->setAnimationSpeed(MOVE_LEFT, 8);
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.25f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.5f));
		
		sprite->setAnimationSpeed(MOVE_RIGHT, 8);
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25, 0.f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25, 0.25f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25, 0.5f));
		
	sprite->changeAnimation(1);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	
}

void Character::update(int deltaTime)
{
	sprite->update(deltaTime);
	if(Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{
		if(sprite->animation() != MOVE_LEFT)
			sprite->changeAnimation(MOVE_LEFT);
		posPlayer.x -= 2;
		if(map->collisionMoveLeft(posPlayer, glm::ivec2(32, 32)))
		{
			posPlayer.x += 2;
			sprite->changeAnimation(STAND_LEFT);
		}
	}
	else if(Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{
		if(sprite->animation() != MOVE_RIGHT)
			sprite->changeAnimation(MOVE_RIGHT);
		posPlayer.x += 2;
		if(map->collisionMoveRight(posPlayer, glm::ivec2(32, 32)))
		{
			posPlayer.x -= 2;
			sprite->changeAnimation(STAND_RIGHT);
		}
	}
	else {
		if(sprite->animation() == MOVE_LEFT)
			sprite->changeAnimation(STAND_LEFT);
		else if(sprite->animation() == MOVE_RIGHT)
			sprite->changeAnimation(STAND_RIGHT);
	}
	
	if (bJumping) {//Player at the air
		jumpAngle += JUMP_ANGLE_STEP;
		if(jumpAngle == 180) { //Very near the ground
			bJumping = false;
			posPlayer.y = startY;
		}
		else {//going up when 0<=jumpAngle<=90, down when 90<jumpAngle<=180
			posPlayer.y = int(startY - JUMP_HEIGHT * sin(3.14159f * jumpAngle / 180.f));
			if (map->collisionMoveUp(posPlayer, glm::ivec2(32, 32))) {
				posPlayer.y = int(startY - JUMP_HEIGHT * sin(3.14159f * (jumpAngle - JUMP_ANGLE_STEP) / 180.f));//Undo movement
				bJumping = false;
				bHoving = true;
			}
			else if (jumpAngle > 90) { //starting to go down, from this point the sinus function will be decreasing
				bJumping = !map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y);
				bHoving = true;
			}
		}
	}
	else {
		posPlayer.y += FALL_STEP;//going down
		if(map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y)) {
			if(Game::instance().getSpecialKey(GLUT_KEY_UP)) {
				nJumps = 1;
				bHoving = false;
				bJumping = true;
				jumpAngle = 0;
				startY = posPlayer.y;
			}
		}
	}

	if (bHoving && Game::instance().getSpecialKey(GLUT_KEY_UP) && nJumps < MAX_JUMPS) {
		nJumps++;
		bHoving = false;
		bJumping = true;
		jumpAngle = 0;
		startY = posPlayer.y;
		//sprite->changeAnimation(HOVING); TODO
	}

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
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
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

glm::vec2 Character::getPosition() {
	return glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y));
}




