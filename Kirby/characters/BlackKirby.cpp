//
// Created by quokka on 20/10/16.
//

#include "BlackKirby.h"

BlackKirby::BlackKirby() {

    setPathToSpriteSheet("images/black_kirby_spritesheet.png");

    mSpriteRows = 11;
    mNumberAnimations = 11;

    mNumDeath = 8;
    mNumFly = 6;
    mNumSwallow = 2;
}
