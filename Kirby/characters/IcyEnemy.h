//
// Created by quokka on 29/10/16.
//

#ifndef KIRBY_ICYENEMY_H
#define KIRBY_ICYENEMY_H

#pragma once
#include "BaseEnemy.h"
#include "WalkingDummyEnemy.h"
#include "../objects/BigObject.h"

class IcyEnemy :  public WalkingDummyEnemy
{

public:
    IcyEnemy();
    ~IcyEnemy() {}

    void init(ShaderProgram &shaderProgram, Scene* scene);
    void update(int deltaTime);
    void render();

    BigObject* getIce() { return mIce; }

    PowerType getType() const {
        return PowerType::Ice;
    };
private:
    BigObject* mIce;

};

#endif //KIRBY_ICYENEMY_H
