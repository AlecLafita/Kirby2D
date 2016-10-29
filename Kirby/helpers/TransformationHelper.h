//
// Created by quokka on 20/10/16.
//

#ifndef PROJECT_TRANSFORMATIONHELPER_H
#define PROJECT_TRANSFORMATIONHELPER_H

#include "../base/ShaderProgram.h"
#include "../characters/Player.h"
#include "../characters/FireKirby.h"
#include "../characters/Kirby.h"
#include "../characters/BlackKirby.h"
#include "../characters/AquaKirby.h"
#include "../characters/BaseEnemy.h"
#include "../characters/IceKirby.h"

class TransformationHelper {

public:

    TransformationHelper();

    void init();
    Player* transformPlayer(Player* player, const BaseEnemy* enemy,
                         ShaderProgram& shaderProgram, Scene* scene) const;

private:

};


#endif //PROJECT_TRANSFORMATIONHELPER_H
