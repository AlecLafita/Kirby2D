
#include "AttackEnemy.h"
#include "../base/Scene.h"
#include "../objects/ProjectileObject.h"

AttackEnemy::AttackEnemy()
{
    dir = glm::ivec2(-1, 0);

    //Character::setPathToSpriteSheet("images/snowy_enemy_spritesheet.png");

    mNumberAnimations = 8;

    mSpriteRows = 6;

    mNumStand = 4;
    mNumMove = 4;
    mNumAttack = 4;
    mNumFly = 0;

    //Sprite rows
    START_ROW_STAND_RIGHT = 0;
    START_ROW_STAND_LEFT = 1;
    START_ROW_MOVE_RIGHT = 2;
    START_ROW_MOVE_LEFT = 3;
    START_ROW_ATTACK_RIGHT = 4;
    START_ROW_ATTACK_LEFT = 5;
}


void AttackEnemy::init(ShaderProgram &shaderProgram, Scene *scene){

    WalkingDummyEnemy::init(shaderProgram, scene);
    sprite->changeAnimation(MOVE_LEFT);
}


void AttackEnemy::update(int deltaTime){

    //if (isInFrustrum()) {

    if (isAttacking) {
        if (computeAttack()) {
            BaseEnemy::update(deltaTime);
            mAttack->update(deltaTime);
            return;
        }
    }


    searchPlayer();
    //Move to corresponding direction
    posCharacter += dir;
    if (dir.x < 0) { //Go left
        if (mScene->collisionMoveLeft(this)) {
            sprite->changeAnimation(MOVE_RIGHT);
            posCharacter -= dir;
            dir = -dir;
        }
    }
    else { //Go right
        if (mScene->collisionMoveRight(this)) {
            sprite->changeAnimation(MOVE_LEFT);
            posCharacter -= dir;
            dir = -dir;
        }
    }

    posCharacter.y += FALL_STEP;//going down
    bool atGround = mScene->collisionMoveDown(this); //if it's at floor, will undo previous increment, otherwise will fall
    if (!isAttacking && atGround) {
        int ran = rand() % 3000;
        if (ran > 2000 && ran < 2030) {// start attacking
            if (dir.x > 0)  {
                sprite->changeAnimation(ATTACK_RIGHT);
                mAttack->setRightAnimation();
                if (ProjectileObject* mProjectile = dynamic_cast<ProjectileObject*>(mAttack)){
                    mProjectile->setDirection(glm::ivec2(1,0));
                    mProjectile->setPosition(glm::ivec2(posCharacter.x + getSize().x, posCharacter.y+15));
                }
                else
                    mAttack->setPosition(glm::ivec2(posCharacter.x + getSize().x, posCharacter.y));
            }
            else {
                sprite->changeAnimation(ATTACK_LEFT);
                mAttack->setLeftAnimation();
                if (ProjectileObject* mProjectile = dynamic_cast<ProjectileObject*>(mAttack)) {
                    mProjectile->setDirection(glm::ivec2(-1,0));
                    mProjectile->setPosition(glm::ivec2(posCharacter.x - BIG_OBJECT_SIZE_X, posCharacter.y+15));
                }
                else
                    mAttack->setPosition(glm::ivec2(posCharacter.x - BIG_OBJECT_SIZE_X, posCharacter.y));
            }
            isAttacking = true;
            mAttack->forceNotIsTook();
        }
    }
    BaseEnemy::update(deltaTime);
    //}
}

void AttackEnemy::render() {
    BaseEnemy::render();
    if (isAttacking) mAttack->render();
}