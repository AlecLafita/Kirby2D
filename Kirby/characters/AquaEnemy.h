//
// Created by quokka on 31/10/16.
//

#ifndef KIRBY_AQUAENEMY_H
#define KIRBY_AQUAENEMY_H

#pragma once
#include "BaseEnemy.h"
#include "AttackEnemy.h"
#include "../objects/BigObject.h"

class AquaEnemy :  public AttackEnemy
{

public:
    AquaEnemy();
    ~AquaEnemy() {}

    void init(ShaderProgram &shaderProgram, Scene* scene);
    //void update(int deltaTime);
    //void render();

    //BigObject* getAqua() { return mAqua; }

    PowerType getType() const {
        return PowerType::Aqua;
    };
protected:
    bool computeAttack();

};
#endif //KIRBY_AQUAENEMY_H
