//
// Created by quokka on 26/10/16.
//

#ifndef KIRBY_ATTACKENEMY_H
#define KIRBY_ATTACKENEMY_H

#include "BaseEnemy.h"
#include "WalkingDummyEnemy.h"
#include "../objects/BaseObject.h"

class AttackEnemy :  public WalkingDummyEnemy { //Abstract class!

public:
    AttackEnemy();
    ~AttackEnemy() {}

    void init(ShaderProgram &shaderProgram, Scene* scene);
    void update(int deltaTime);
	void render();

	virtual BaseObject* getAttack() { return mAttack; }

protected:
	virtual bool computeAttack() {return false;} //Returns if enemy should stop attacking

protected:
	BaseObject* mAttack;


};

#endif //KIRBY_ATTACKENEMY_H
