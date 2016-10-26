#pragma once
#include "Character.h"
#include "PowerType.h"

class BaseEnemy : public Character
{

public:
	BaseEnemy();
	~BaseEnemy();

	virtual void init(ShaderProgram &shaderProgram,Scene* scene);
	virtual void update(int deltaTime);

	virtual int getScore(){ return 200; }

	PowerType getType() const {
        return PowerType::Normal;
    };

protected:
	bool isInFrustrum();
	
	glm::ivec2 dir; //Direction of the enemy to go 

};

