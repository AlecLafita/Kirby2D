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
	if (isInFrustrum()){
		posCharacter += dir;
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
		BaseEnemy::update(deltaTime);
	}
}
