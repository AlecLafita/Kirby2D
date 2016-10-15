#include "BaseEnemy.h"
#include "Scene.h"

BaseEnemy::BaseEnemy(){
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
				//return;
		}
		Character::update(deltaTime);
		//TODO: Implement IA Here!
	}
}

bool BaseEnemy::isInFrustrum(){

	return true;
}