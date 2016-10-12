#include "BaseEnemy.h"


class PinxoEnemy : public BaseEnemy {

public:
    PinxoEnemy();
    ~PinxoEnemy();

    void init(ShaderProgram &shaderProgram);
    void update(int deltaTime);

protected:

};
