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
#include "../characters/BaseEnemy.h"

class TransformationHelper {

public:

    TransformationHelper();

    void init();
    void transformPlayer(Player* player, const BaseEnemy* enemy,
                         ShaderProgram& shaderProgram, Scene* scene) const;

private:

    const ShaderProgram mShader;
    Scene* mScene;
};


#endif //PROJECT_TRANSFORMATIONHELPER_H
