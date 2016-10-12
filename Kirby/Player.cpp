#include "Player.h"
#include <GL/glut.h>
#include "Game.h"

Player::Player()
{
	mNumberAnimations = 4;
}

void Player::init(ShaderProgram &shaderProgram){
	
	Character::init(shaderProgram);
	bHoving = false;
	nJumps = 0;
}

void Player::update(int deltaTime){

	computeNextMove();
	Character::update(deltaTime);
}

void Player::computeNextMove() {

	if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{
		if (sprite->animation() != MOVE_LEFT)
			sprite->changeAnimation(MOVE_LEFT);
		posCharacter.x -= MOVEMENT_DEFAULT;
		if (map->collisionMoveLeft(posCharacter, glm::ivec2(TILE_SIZE_X, TILE_SIZE_Y)))
		{
			posCharacter.x += MOVEMENT_DEFAULT;
			sprite->changeAnimation(STAND_LEFT);
		}
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{
		if (sprite->animation() != MOVE_RIGHT)
			sprite->changeAnimation(MOVE_RIGHT);
		posCharacter.x += MOVEMENT_DEFAULT;
		if (map->collisionMoveRight(posCharacter, glm::ivec2(TILE_SIZE_X, TILE_SIZE_X)))
		{
			posCharacter.x -= MOVEMENT_DEFAULT;
			sprite->changeAnimation(STAND_RIGHT);
		}
	}
	else {
		if (sprite->animation() == MOVE_LEFT)
			sprite->changeAnimation(STAND_LEFT);
		else if (sprite->animation() == MOVE_RIGHT)
			sprite->changeAnimation(STAND_RIGHT);
	}

	if (bJumping) {//Player at the air
		jumpAngle += JUMP_ANGLE_STEP;
		if (jumpAngle == ANGLE_GROUND) { //Very near the ground
			bJumping = false;
			posCharacter.y = startY;
		}
		else {//going up when 0<=jumpAngle<=90, down when 90<jumpAngle<=180
			posCharacter.y = int(startY - JUMP_HEIGHT * sin(3.14159f * jumpAngle / 180.f));
			if (map->collisionMoveUp(posCharacter, glm::ivec2(TILE_SIZE_X, TILE_SIZE_Y))) {
				posCharacter.y = int(startY - JUMP_HEIGHT * sin(3.14159f * (jumpAngle - JUMP_ANGLE_STEP) / 180.f));//Undo movement
				bJumping = false;
				bHoving = true;
			}
			else if (jumpAngle > 90) { //starting to go down, from this point the sinus function will be decreasing
				bJumping = !map->collisionMoveDown(posCharacter, glm::ivec2(TILE_SIZE_X, TILE_SIZE_Y), &posCharacter.y);
				bHoving = true;
			}
		}
	}
	else {
		posCharacter.y += FALL_STEP;//going down
		if (map->collisionMoveDown(posCharacter, glm::ivec2(32, 32), &posCharacter.y)) {
			if (Game::instance().getSpecialKey(GLUT_KEY_UP)) {
				nJumps = 1;
				bHoving = false;
				bJumping = true;
				jumpAngle = 0;
				startY = posCharacter.y;
			}
		}
	}

	if (bHoving && Game::instance().getSpecialKey(GLUT_KEY_UP) && nJumps < MAX_JUMPS) {
		nJumps++;
		bHoving = false;
		bJumping = true;
		jumpAngle = 0;
		startY = posCharacter.y;
		//sprite->changeAnimation(HOVING); TODO
	}
}

Player::~Player()
{
}
