//
// Created by quokka on 20/10/16.
//


#include "Kirby.h"

Kirby::Kirby() {

    setPathToSpriteSheet("images/kirby_spritesheet.png");
    mSpriteRows = 10;

    mNumFlyLeft = mNumFlyRight = 6;
    mNumSwallowLeft = mNumSwallowRight = 2;
}

void Kirby::init(ShaderProgram &shaderProgram, Scene *scene) {

    Character::init(shaderProgram, scene);

}