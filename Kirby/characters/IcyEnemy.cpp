//
// Created by quokka on 29/10/16.
//

//
// Created by quokka on 26/10/16.
//

#include "IcyEnemy.h"
#include "../base/Scene.h"
#include "../objects/ProjectileObject.h"

IcyEnemy::IcyEnemy()
{

    Character::setPathToSpriteSheet("images/snowy_enemy_spritesheet.png");
}


void IcyEnemy::init(ShaderProgram &shaderProgram, Scene *scene){
    AttackEnemy::init(shaderProgram, scene);

    mAttack = new ProjectileObject();
    mAttack->setPathToSpriteSheet("images/arrow.png");
    mAttack->init(shaderProgram, scene);
    ProjectileObject* mProjectile = dynamic_cast<ProjectileObject*>(mAttack);
    mProjectile->setDirection(glm::ivec2(1,0));
}

bool IcyEnemy::computeAttack() {
    int ran = rand() % 3000;
    if (ran > 1000 && ran < 1050) {// stop
        if (dir.x > 0) sprite->changeAnimation(STAND_RIGHT);
        else sprite->changeAnimation(STAND_LEFT);
        isAttacking = false;
        mAttack->setPosition(glm::ivec2(-100, -100));//Set object to invalid position in order to not collide
    	ProjectileObject* mProjectile = dynamic_cast<ProjectileObject*>(mAttack);
    	mProjectile->setDirection(glm::ivec2(0,0));
    	return false;
    }
    else { //continue attacking
    	return true;
	}
}