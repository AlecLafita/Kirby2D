//
// Created by quokka on 29/10/16.
//

#ifndef KIRBY_ICEKIRBY_H
#define KIRBY_ICEKIRBY_H

#include "Player.h"
#include "../objects/ProjectileObject.h"


class IceKirby : public Player {
public:
    IceKirby();
    ~IceKirby() {}

    void init(ShaderProgram &shaderProgram, Scene* scene);
    void update(int deltaTime);
    void render();

    glm::ivec2 getCollisionPosition() const { return getPosition() +glm::ivec2(6,5);}
    glm::ivec2 getCollisionSize() const {return getSize() -glm::ivec2(12,5);}

    ProjectileObject* getIce() { return mIce; }

protected:
    //void computeAttack();
    //void computeMovement();
    //void computeJump();
    int getAttackSound();

private:
    ProjectileObject* mIce;
    bool firstAttack;
};
#endif //KIRBY_ICEKIRBY_H
