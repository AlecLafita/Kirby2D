//
// Created by quokka on 29/10/16.
//

#include "IceKirby.h"
#include "../base/Game.h"

#include <iostream>
using namespace std;

IceKirby::IceKirby()
{
    setPathToSpriteSheet("images/ice_kirby_spritesheet.png");
    mSpriteRows = 10;

    //mSpriteRows = 11;
    mNumberAnimations = 11 ;

    mAttackSoundTime = 1300;
    mNumDeath = 3;
    mNumFly = 6;
    mNumSwallow = 2;
    mNumAttack = 2;

    START_ROW_DEATH = 9;

    firstAttack = true;
}

void IceKirby::init(ShaderProgram &shaderProgram, Scene* scene) {
    Player::init(shaderProgram, scene);
    //Creae fire object
    mIce = new ProjectileObject();
    mIce->setPathToSpriteSheet("images/arrow.png"); //OBJECT SPRITESHEET
    //mIce->setTexturePosition(glm::fvec2(0.25f, 0.25f)); //POSITION IN SPRITESHEET
    mIce->init(shaderProgram, scene);
    mIce->setPosition(glm::ivec2(-100, -100));
    mIce->setDirection(glm::ivec2(0,0));
}

void IceKirby::update(int deltaTime) {
    Player::update(deltaTime);
    if (bAttacking && (Game::instance().getKey('a') || Game::instance().getKey('A') )) {
        //mIce->forceNotIsTook();
        if (isLeftDirection()) {
            if (firstAttack) {
                mIce->setPosition(glm::ivec2(posCharacter.x - BIG_OBJECT_SIZE_X, posCharacter.y));
                firstAttack = false;
                mIce->setDirection(glm::ivec2(-2,0));
                mIce->setLeftAnimation();
                mIce->forceNotIsTook();
            }
        }
        else {
            if (firstAttack) {
                mIce->setPosition(glm::ivec2(posCharacter.x + getSize().x, posCharacter.y));
                firstAttack = false;
                mIce->setDirection(glm::ivec2(2,0));
                mIce->setRightAnimation();
                mIce->forceNotIsTook();
            }
        }
    }

    else {
        firstAttack = true;
    }


    if (!mIce->isTaken()) 
        mIce->update(deltaTime);
    else {
        firstAttack = true;
        mIce->setPosition(glm::ivec2(-100, -100));
        mIce->setDirection(glm::ivec2(0,0));
    }
}

void IceKirby::render() {
    Player::render();
    mIce->render();
}


int IceKirby::getAttackSound() {
    return SOUND_FIRE; //TODO: Change this to ice
}