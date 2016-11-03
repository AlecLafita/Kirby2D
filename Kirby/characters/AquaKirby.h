#ifndef PROJECT_KIRBY_AQUA_H
#define PROJECT_KIRBY_AQUA_H

#include "Player.h"
#include "../objects/RotationObject.h"

class AquaKirby : public Player {
public:
    AquaKirby();
    ~AquaKirby() {}

    void init(ShaderProgram &shaderProgram, Scene* scene);
    void update(int deltaTime);
    void render();

    glm::ivec2 getCollisionPosition() const { return getPosition() +glm::ivec2(6,5);}
    glm::ivec2 getCollisionSize() const {return getSize() -glm::ivec2(12,5);}

    RotationObject* getAqua() { return mAqua; }

protected:
    //void computeAttack();
    //void computeMovement();
    //void computeJump();
    int getAttackSound();

private:
    RotationObject* mAqua;
};

#endif
