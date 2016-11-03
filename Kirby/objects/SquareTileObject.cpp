//
// Created by quokka on 01/11/16.
//

#include "SquareTileObject.h"
#include "../base/Scene.h"

SquareTileObject::SquareTileObject() {

    setPathToSpriteSheet(TILE_MOVABLE_PATH);
    mNumberAnimations = 1;
    bTaken = false;
    sizeInSpriteSheetX = sizeInSpriteSheetY = 1;
}


void SquareTileObject::init(ShaderProgram &shaderProgram, Scene* scene) {

    mScene = scene;
    BaseObject::init(shaderProgram, scene);
}

void SquareTileObject::update(int deltaTime) {

    if(mScene->playerCanSwallow(this)){

        bTaken = true;
    }
    BaseObject::update(deltaTime);
}