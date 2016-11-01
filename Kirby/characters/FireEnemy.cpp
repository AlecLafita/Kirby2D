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
	mAttack->setPathToSpriteSheet(BIG_OBJECTS_FIRE_PATH); //OBJECT SPRITESHEET
	mAttack->init(shaderProgram, scene);

}
