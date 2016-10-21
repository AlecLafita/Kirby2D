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
void TransformationHelper::transformPlayer(Player* player, const BaseEnemy *enemy, ShaderProgram& shaderProgram, Scene* scene) const {

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
            player = new BlackKirby();
            break;
    }

    player->init(shaderProgram, scene);
    player->setPosition(glm::vec2(16, 16));
}