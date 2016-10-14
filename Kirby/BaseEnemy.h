#pragma once
#include "Character.h"

class BaseEnemy : public Character
{

public:
	BaseEnemy();
	~BaseEnemy();

	void init(ShaderProgram &shaderProgram,Scene* scene);
	void update(int deltaTime);

	//virtual int enemyName();

protected:
	bool isInFrustrum();
};

