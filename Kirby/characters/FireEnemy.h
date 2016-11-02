//
// Created by quokka on 26/10/16.
//

#ifndef KIRBY_FIREENEMY_H
#define KIRBY_FIREENEMY_H

#pragma once
#include "BaseEnemy.h"
#include "AttackEnemy.h"
#include "../objects/BigObject.h"

class FireEnemy :  public AttackEnemy
{

public:
    FireEnemy();
    ~FireEnemy() {}

    void init(ShaderProgram &shaderProgram, Scene* scene);
    //void update(int deltaTime);
	//void render();

	//BigObject* getFire() { return mFire; }

    PowerType getType() const {
        return PowerType::Fire;
    };


protected:
    bool computeAttack();

};

#endif //KIRBY_FIREENEMY_H
