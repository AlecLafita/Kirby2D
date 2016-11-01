//
// Created by quokka on 01/11/16.
//

#ifndef KIRBY_DOOROBJECT_H
#define KIRBY_DOOROBJECT_H

#include "BaseObject.h"
#include "../base/Defines.h"

class DoorObject : public BaseObject
{
public:
    DoorObject();
    ~DoorObject() {}

    void init(ShaderProgram &shaderProgram, Scene* scene);

    void update(int deltaTime);

private:

};


#endif //KIRBY_DOOROBJECT_H
