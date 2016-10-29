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
    //Creae fire object
    mAqua = new BigObject();
    mAqua->setPathToSpriteSheet(BIG_OBJECTS_AQUA_PATH); //OBJECT SPRITESHEET
    //mAqua->setTexturePosition(glm::fvec2(0.25f, 0.25f)); //POSITION IN SPRITESHEET
    mAqua->init(shaderProgram, scene);
}

void AquaKirby::update(int deltaTime) {
    Player::update(deltaTime);
    if (bAttacking && (Game::instance().getKey('a') || Game::instance().getKey('A') )) {
        if (isLeftDirection()) {
            mAqua->setPosition(glm::ivec2(posCharacter.x - BIG_OBJECT_SIZE_X, posCharacter.y));
            mAqua->update(deltaTime);
        }
        else {
            mAqua->setPosition(glm::ivec2(posCharacter.x + getSize().x, posCharacter.y));
            mAqua->update(deltaTime);
        }
    }
    else {
        mAqua->setPosition(glm::ivec2(-100, -100));//Set object to invalid position in order to not collide
        if (isLeftDirection()) mAqua->setLeftAnimation();
        else mAqua->setRightAnimation();
    }
}

void AquaKirby::render() {
    Player::render();
    if (bAttacking && (Game::instance().getKey('a') || Game::instance().getKey('A')))
        mAqua->render();
}


int AquaKirby::getAttackSound() {
    return SOUND_FIRE;
}