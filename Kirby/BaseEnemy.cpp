#include "BaseEnemy.h"


BaseEnemy::BaseEnemy(){
}


BaseEnemy::~BaseEnemy() {
}


void BaseEnemy::init(ShaderProgram &shaderProgram){

	Character::init(shaderProgram);

}

void BaseEnemy::update(int deltaTime){

	if (isInFrustrum()){

		Character::update(deltaTime);
		//TODO: Implement IA Here!
	}
}

bool BaseEnemy::isInFrustrum(){

	return true;
}