//
// Created by quokka on 26/10/16.
//

#include "FireEnemy.h"
#include "../base/Scene.h"


FireEnemy::FireEnemy()
{
    dir = glm::ivec2(-1, 0);

    Character::setPathToSpriteSheet("images/firy_enemy_spritesheet.png");

    mNumberAnimations = 8;

    mSpriteRows = 6;

    mNumStand = 2;
    mNumMove = 4;
    mNumAttack = 2;
    mNumFly = 0;

    //Sprite rows
    START_ROW_STAND_RIGHT = 0;
    START_ROW_STAND_LEFT = 1;
    START_ROW_MOVE_RIGHT = 2;
    START_ROW_MOVE_LEFT = 3;
    START_ROW_ATTACK_RIGHT = 4;
    START_ROW_ATTACK_LEFT = 5;
}


void FireEnemy::init(ShaderProgram &shaderProgram, Scene *scene){

    WalkingDummyEnemy::init(shaderProgram, scene);
    sprite->changeAnimation(MOVE_RIGHT);
}


void FireEnemy::update(int deltaTime){

    //if (isInFrustrum()) {

    glm::ivec2 playerPos = mScene->getPlayer()->getPosition();

    int diffTilesX = (int)(playerPos.x - posCharacter.x) / TILE_SIZE_X;
    int diffTilesY = (int)(playerPos.y - posCharacter.y) / TILE_SIZE_X;

    //Minor than 3 tiles, go after him!
    if(abs(diffTilesX) < 3 && abs(diffTilesY) < 2){

        if(diffTilesX < 0){
            //Left of him!
            if(sprite->animation() != MOVE_LEFT){
                sprite->changeAnimation(MOVE_LEFT);
                posCharacter -= dir;
                dir = -dir;
            }
        } else if(diffTilesX > 0){
            //RIGHT of him!
            if(sprite->animation() != MOVE_RIGHT){
                sprite->changeAnimation(MOVE_RIGHT);
                posCharacter -= dir;
                dir = -dir;
            }

        } else {
            //Just above him!
            //Do nothing :D
        }
    } else {
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
    }
    posCharacter += dir;
    BaseEnemy::update(deltaTime);
    //}
}
