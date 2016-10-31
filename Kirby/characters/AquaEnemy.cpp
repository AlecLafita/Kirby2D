//
// Created by quokka on 31/10/16.
//


#include "AquaEnemy.h"
#include "../base/Scene.h"


AquaEnemy::AquaEnemy() {
    Character::setPathToSpriteSheet("images/aqua_enemy_spritesheet.png");

    //Sprite rows
    START_ROW_STAND_RIGHT = START_ROW_ATTACK_RIGHT = 0;
    START_ROW_STAND_LEFT = START_ROW_ATTACK_LEFT = 1;
    START_ROW_MOVE_RIGHT = 2;
    START_ROW_MOVE_LEFT = 3;
}


void AquaEnemy::init(ShaderProgram &shaderProgram, Scene *scene){

    AttackEnemy::init(shaderProgram, scene);

    mAttack->setPathToSpriteSheet(BIG_OBJECTS_FIRE_PATH); //OBJECT SPRITESHEET
    mAttack->init(shaderProgram, scene);

}