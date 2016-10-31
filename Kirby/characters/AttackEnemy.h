//
// Created by quokka on 26/10/16.
//

#ifndef KIRBY_ATTACKENEMY_H
#define KIRBY_ATTACKENEMY_H

#include "BaseEnemy.h"
#include "WalkingDummyEnemy.h"
#include "../objects/BigObject.h"

class AttackEnemy :  public WalkingDummyEnemy { //Abstract class!

public:
    AttackEnemy();
    ~AttackEnemy() {}

    void init(ShaderProgram &shaderProgram, Scene* scene);
    void update(int deltaTime);
	void render();

	virtual BigObject* getAttack() { return mAttack; }

protected:
	BigObject* mAttack;

};

#endif //KIRBY_ATTACKENEMY_H
