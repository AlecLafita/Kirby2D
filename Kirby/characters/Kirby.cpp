//
// Created by quokka on 20/10/16.
//


#include "Kirby.h"

Kirby::Kirby() {

    setPathToSpriteSheet("images/kirby_spritesheet.png");
    mSpriteRows = 10;
    mNumberAnimations = 10;

    mNumFly = 6;
    mNumSwallow = 2;
}

void Kirby::init(ShaderProgram &shaderProgram, Scene *scene) {

    Character::init(shaderProgram, scene);

}