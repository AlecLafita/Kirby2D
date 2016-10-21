#pragma once
#include "BaseEnemy.h"


class PinxoEnemy : public BaseEnemy {

public:
    PinxoEnemy();
    ~PinxoEnemy();

    void init(ShaderProgram &shaderProgram,Scene* scene);
    void update(int deltaTime);

    PowerType getType() const {
        return PowerType::Normal;
    }

protected:

};
