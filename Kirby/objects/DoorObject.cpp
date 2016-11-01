//
// Created by quokka on 01/11/16.
//

#include "DoorObject.h"
#include "../base/Scene.h"

DoorObject::DoorObject() {

    setPathToSpriteSheet(TILE_MOVABLE_PATH);
    mNumberAnimations = 1;
    bTaken = false;

    sizeInSpriteSheetX = sizeInSpriteSheetY = 1;
}



void DoorObject::init(ShaderProgram &shaderProgram, Scene* scene) {
    mScene = scene;

    BaseObject::init(shaderProgram, scene);
}

void DoorObject::update(int deltaTime) {

    if(!mScene->playerTakesDoorNextLevel(this)){

        BaseObject::update(deltaTime);
    }
}