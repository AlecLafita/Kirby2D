#include "AquaKirby.h"
#include "../base/Game.h"

#include <iostream>
using namespace std;

AquaKirby::AquaKirby()
{
    setPathToSpriteSheet("images/aqua_kirby_spritesheet.png");
    mSpriteRows = 10;

    //mSpriteRows = 11;
    mNumberAnimations = 10;

    mAttackSoundTime = 1300;
    mNumDeath = 8;
    mNumFly = 6;
    mNumSwallow = 2;

    START_ROW_DEATH = 9;
}

void AquaKirby::init(ShaderProgram &shaderProgram, Scene* scene) {
    Player::init(shaderProgram, scene);
    //Creae aqua object
    mAqua = new RotationObject();
    mAqua->setPathToSpriteSheet(BIG_OBJECTS_AQUA_PATH); //OBJECT SPRITESHEET
    mAqua->init(shaderProgram, scene);
    glm::ivec2 sizeChar = getSize();
    mAqua->setRadius(max(sizeChar.x,sizeChar.y));
}

void AquaKirby::update(int deltaTime) {
    Player::update(deltaTime);

    if (bAttacking && (Game::instance().getKey('a') || Game::instance().getKey('A') )) {
        mAqua->setCentralPosChar(posCharacter + getSize()/2);
        if (isLeftDirection()) 
            mAqua->setLeftRotation();
        else 
            mAqua->setRightRotation();
        mAqua->update(deltaTime);
    }
    else {
        mAqua->setPosition(glm::ivec2(-100, -100));//Set object to invalid position in order to not collide
        if (isLeftDirection()) mAqua->setLeftAnimation();
        else mAqua->setRightAnimation();
    }
}

void AquaKirby::render() {
    Player::render();
    //mAttackTime <= mAttackSoundTime
    if (mAttackTime <= mAttackSoundTime && !bAnimating)
        mAqua->render();
}


int AquaKirby::getAttackSound() {
    return SOUND_FIRE; //TODO: Change for another one
}