//
// Created by quokka on 26/10/16.
//

#include "FireEnemy.h"
#include "../base/Scene.h"


FireEnemy::FireEnemy()
{

    Character::setPathToSpriteSheet("images/firy_enemy_spritesheet.png");
}


void FireEnemy::init(ShaderProgram &shaderProgram, Scene *scene){
	AttackEnemy::init(shaderProgram, scene);
	
	mAttack = new BigObject();
	mAttack->setPathToSpriteSheet(BIG_OBJECTS_FIRE_PATH); //OBJECT SPRITESHEET
	mAttack->init(shaderProgram, scene);

}

bool FireEnemy::computeAttack() {
    //Maybe stop attacking
    int ran = rand() % 3000;
    if (ran > 1000 && ran < 1050) {// stop
        if (dir.x > 0) sprite->changeAnimation(MOVE_RIGHT);
        else sprite->changeAnimation(MOVE_LEFT);
        isAttacking = false;
        mAttack->setPosition(glm::ivec2(-100, -100));//Set object to invalid position in order to not collide
    	return false;
    }
    else { //continue attacking
    	return true;
	}
}