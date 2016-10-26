//
// Created by quokka on 26/10/16.
//

#ifndef KIRBY_FIREENEMY_H
#define KIRBY_FIREENEMY_H

#pragma once
#include "BaseEnemy.h"
#include "WalkingDummyEnemy.h"

class FireEnemy :
        public WalkingDummyEnemy
{

public:
    FireEnemy();
    ~FireEnemy() {}

    void init(ShaderProgram &shaderProgram, Scene* scene);
    void update(int deltaTime);

    PowerType getType() const {
        return PowerType::Fire;
    };

};

#endif //KIRBY_FIREENEMY_H
