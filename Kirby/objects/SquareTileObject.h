//
// Created by quokka on 03/11/16.
//

#ifndef KIRBY_SQUARETILEOBJECT_H
#define KIRBY_SQUARETILEOBJECT_H

#include "BaseObject.h"
#include "../base/Defines.h"

class SquareTileObject : public BaseObject
{
public:
    SquareTileObject();
    ~SquareTileObject() {}

    void init(ShaderProgram &shaderProgram, Scene* scene);

    void update(int deltaTime);
    int getScore() { return 300; }

private:

};
#endif //KIRBY_SQUARETILEOBJECT_H
