#include "BaseEnemy.h"


BaseEnemy::BaseEnemy(){
}


BaseEnemy::~BaseEnemy() {
}


void BaseEnemy::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram){

	Character::init(tileMapPos, shaderProgram);

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