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
    mNumberAnimations = 9;

    mAttackSoundTime = 1300;
    mNumDeath = 3;
    mNumFly = 6;
    mNumSwallow = 2;

    START_ROW_DEATH = 9;
}

void IceKirby::init(ShaderProgram &shaderProgram, Scene* scene) {
    Player::init(shaderProgram, scene);
    //Creae fire object
    mIce = new BigObject();
    mIce->setPathToSpriteSheet(BIG_OBJECTS_ICE_PATH); //OBJECT SPRITESHEET
    //mIce->setTexturePosition(glm::fvec2(0.25f, 0.25f)); //POSITION IN SPRITESHEET
    mIce->init(shaderProgram, scene);
}

void IceKirby::update(int deltaTime) {
    Player::update(deltaTime);
    if (bAttacking && (Game::instance().getKey('a') || Game::instance().getKey('A') )) {
        if (isLeftDirection()) {
            mIce->setPosition(glm::ivec2(posCharacter.x - BIG_OBJECT_SIZE_X, posCharacter.y));
            mIce->update(deltaTime);
        }
        else {
            mIce->setPosition(glm::ivec2(posCharacter.x + getSize().x, posCharacter.y));
            mIce->update(deltaTime);
        }
    }
    else {
        mIce->setPosition(glm::ivec2(-100, -100));//Set object to invalid position in order to not collide
        if (isLeftDirection()) mIce->setLeftAnimation();
        else mIce->setRightAnimation();
    }
}

void IceKirby::render() {
    Player::render();
    if (bAttacking && (Game::instance().getKey('a') || Game::instance().getKey('A')))
        mIce->render();
}


int IceKirby::getAttackSound() {
    return SOUND_FIRE; //TODO: Change this to ice
}