#ifndef PROJECT_KIRBY_FIRE_H
#define PROJECT_KIRBY_FIRE_H

#include "Player.h"
#include "../objects/BigObject.h"

class FireKirby : public Player {
public:
	FireKirby();
	~FireKirby() {}

	void init(ShaderProgram &shaderProgram, Scene* scene);
	void update(int deltaTime);
	void render();

    glm::ivec2 getCollisionPosition() const { return getPosition() +glm::ivec2(6,5);}
    glm::ivec2 getCollisionSize() const {return getSize() -glm::ivec2(12,5);}
    
	BigObject* getFire() { return mFire; }

protected:
	//void computeAttack();
	//void computeMovement();
	//void computeJump();
	int getAttackSound();

private:
	BigObject* mFire;
};

#endif
