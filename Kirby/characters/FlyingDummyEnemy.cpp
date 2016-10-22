#include "FlyingDummyEnemy.h"
#include "../base/Scene.h"
#include <stdlib.h>     /* srand, rand */


FlyingDummyEnemy::FlyingDummyEnemy() {
	BaseEnemy::BaseEnemy();
	dir = glm::ivec2(-2, 1);
	actY = 0;
}

void FlyingDummyEnemy::init(ShaderProgram &shaderProgram, Scene *scene){

	BaseEnemy::init(shaderProgram, scene);
	sprite->changeAnimation(FLY_LEFT);
}


void FlyingDummyEnemy::update(int deltaTime){

	if (isInFrustrum()){
		//TODO correctly
		posCharacter += dir;
		if (dir.x < 0) { //Go left
			if (mScene->collisionMoveLeft(this)) {
				sprite->changeAnimation(FLY_RIGHT);
				posCharacter -= dir;
				dir = -dir;
			}
		}
		else { //Go right
			if (mScene->collisionMoveRight(this)) {
				sprite->changeAnimation(FLY_LEFT);
				posCharacter -= dir;
				dir = -dir;

			}
		}
		if (dir.y < 0) { //go up
			if (mScene->collisionMoveUp(this)) {
				posCharacter -= dir;
				dir.y = -dir.y;
			}
			/*else if (actY > 50) {
				dir.y = -dir.y;
				actY = 0;
			}*/
		}
		else { //go down
			if (mScene->collisionMoveDown(this)) {
				posCharacter -= dir;
				dir.y = -dir.y;
			}
			/*else if (actY > 50) {
				dir.y = -dir.y;
				actY = 0;
			}*/
		}

		BaseEnemy::update(deltaTime);
		++actY;
	}
}
