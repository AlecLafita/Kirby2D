//
// Created by quokka on 29/10/16.
//

//
// Created by quokka on 26/10/16.
//

#include "IcyEnemy.h"
#include "../base/Scene.h"


IcyEnemy::IcyEnemy()
{

    Character::setPathToSpriteSheet("images/snowy_enemy_spritesheet.png");
}


void IcyEnemy::init(ShaderProgram &shaderProgram, Scene *scene){

    AttackEnemy::init(shaderProgram, scene);
    mAttack->setPathToSpriteSheet(BIG_OBJECTS_ICE_PATH);
    mAttack->init(shaderProgram, scene);

}