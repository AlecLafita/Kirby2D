#ifndef PROJECT_KIRBY_FIRE_H
#define PROJECT_KIRBY_FIRE_H

#include "Player.h"
#include "../objects/BaseObject.h"

class FireKirby : public Player {
public:
	FireKirby();
	~FireKirby() {}

	void init(ShaderProgram &shaderProgram, Scene* scene);
	void update(int deltaTime);
	void render();

protected:
	//void computeAttack();
	/*void computeMovement();
	void computeJump();*/
	int getAttackSound();

private:
	BaseObject* mFire;
};

#endif
