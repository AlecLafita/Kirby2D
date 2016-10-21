#pragma once
#include "Character.h"
#include "PowerType.h"

class BaseEnemy : public Character
{

public:
	BaseEnemy();
	~BaseEnemy();

	void init(ShaderProgram &shaderProgram,Scene* scene);
	void update(int deltaTime);

	PowerType getType() const {
        return PowerType::Normal;
    };

protected:
	bool isInFrustrum();
	
	glm::ivec2 dir; //Direction of the enemy to go 

};

