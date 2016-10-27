#include "WalkingDummyEnemy.h"
#include "../base/Scene.h"


WalkingDummyEnemy::WalkingDummyEnemy()
{
	dir = glm::ivec2(-1, 0);

}


void WalkingDummyEnemy::init(ShaderProgram &shaderProgram, Scene *scene){

	BaseEnemy::init(shaderProgram, scene);
	sprite->changeAnimation(MOVE_LEFT);
}


void WalkingDummyEnemy::update(int deltaTime){

	//if (isInFrustrum()) {
	posCharacter += dir;
	if (mScene->collisionCanFall(this)) {//Near a precipice
		if (dir.x < 0) 
			sprite->changeAnimation(MOVE_RIGHT);
		else 
			sprite->changeAnimation(MOVE_LEFT);
		posCharacter -= dir;
		dir = -dir;
	}
	else {
		if (dir.x < 0) { //Go left
			if (mScene->collisionMoveLeft(this)) {
				sprite->changeAnimation(MOVE_RIGHT);
				posCharacter -= dir;
				dir = -dir;
			}
		}
		else { //Go right
			if (mScene->collisionMoveRight(this)) {
				sprite->changeAnimation(MOVE_LEFT);
				posCharacter -= dir;
				dir = -dir;
			}
		}
	}
	BaseEnemy::update(deltaTime);
	//}
}

void WalkingDummyEnemy::searchPlayer() {
	glm::ivec2 playerPos = mScene->getPlayer()->getPosition();

	int diffTilesX = (int)(playerPos.x - posCharacter.x) / TILE_SIZE_X;
	int diffTilesY = (int)(playerPos.y - posCharacter.y) / TILE_SIZE_X;

	//Minor than 3 tiles, go after player!
	if (abs(diffTilesX) < 3 && abs(diffTilesY) < 2){
		if (diffTilesX > 0){
			//Left of him!
			if (sprite->animation() != MOVE_RIGHT){
				sprite->changeAnimation(MOVE_RIGHT);
				dir.x = -dir.x;
			}
		}
		else if (diffTilesX < 0){
			//RIGHT of him!
			if (sprite->animation() != MOVE_LEFT){
				sprite->changeAnimation(MOVE_LEFT);
				dir.x = -dir.x;
			}
		}
		else {
			//Just above him!
			//Do nothing :D
		}
	}
}