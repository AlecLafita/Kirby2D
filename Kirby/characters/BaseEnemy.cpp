#include <iostream>
#include "BaseEnemy.h"
using namespace std;
#include "../base/Scene.h"


BaseEnemy::BaseEnemy(){
	dir = glm::ivec2(0, 0);
}


BaseEnemy::~BaseEnemy() {
}


void BaseEnemy::init(ShaderProgram &shaderProgram,Scene* scene){

	Character::init(shaderProgram,scene);

}

void BaseEnemy::update(int deltaTime){

	if (isInFrustrum()){
		if (isSwallable) {
			if (mScene->playerCanSwallow(this))
				isDead = true;
		}
		Character::update(deltaTime);
		//TODO: Implement IA Here!
	}
}

bool BaseEnemy::isInFrustrum(){
	int cameraLeft = mScene->getCameraLeftPosition();
	return ((posCharacter.x + CHARACTER_SIZE_X)>cameraLeft && posCharacter.x<(cameraLeft + SCREEN_WIDTH-1));
}