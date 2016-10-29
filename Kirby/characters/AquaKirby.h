#ifndef PROJECT_KIRBY_AQUA_H
#define PROJECT_KIRBY_AQUA_H

#include "Player.h"
#include "../objects/BigObject.h"

class AquaKirby : public Player {
public:
    AquaKirby();
    ~AquaKirby() {}

    void init(ShaderProgram &shaderProgram, Scene* scene);
    void update(int deltaTime);
    void render();

    BigObject* getAqua() { return mAqua; }

protected:
    //void computeAttack();
    //void computeMovement();
    //void computeJump();
    int getAttackSound();

private:
    BigObject* mAqua;
};

#endif
