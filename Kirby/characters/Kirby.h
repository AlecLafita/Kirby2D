//
// Created by quokka on 20/10/16.
//

#ifndef PROJECT_KIRBY_H
#define PROJECT_KIRBY_H

#include "Player.h"

class Kirby : public Player {
public:
    Kirby();
    ~Kirby();

    void init(ShaderProgram &shaderProgram,Scene* scene);

protected:
	//void computeAttack();
	//void computeMovement();
	//void computeJump();
	int getAttackSound();

};


#endif //PROJECT_KIRBY_H
