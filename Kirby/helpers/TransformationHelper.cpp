//
// Created by quokka on 20/10/16.
//
#include <iostream>
#include "TransformationHelper.h"
using namespace std;

/**
 * Creates instance of transformation helper.
 * @return
 */
TransformationHelper::TransformationHelper(){

}

/**
 * Transforms player
 * @param player
 * @param enemy
 */
Player* TransformationHelper::transformPlayer(Player* player, const BaseEnemy *enemy, ShaderProgram& shaderProgram, Scene* scene) const {

    glm::vec2 playerOldPos = player->getPosition();
	int playerOldEnergy = player->getEnergy();
    int startAnim = 0;
    if(!player->isFacingRightSide()){

        startAnim = 1;
    }
    switch (enemy->getType()){

        case PowerType::Fire:
            cout << "Fire type" << endl;
            player = new FireKirby();
            break;

        case PowerType::Steam:
            break;

        case PowerType::Electric:
            cout << "Electric type" << endl;

            break;

        default:
        case PowerType::Normal:
            //Do nothing
            cout << "Normal type" << endl;
            //player = new BlackKirby();
            break;
    }

    player->setStartAnimation(startAnim);
    player->init(shaderProgram, scene);
    player->setPosition(playerOldPos);
	player->setEnergy(playerOldEnergy);
    return player;
}