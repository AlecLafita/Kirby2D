#pragma once
#include "Character.h"

class BaseEnemy : public Character
{

public:
	BaseEnemy();
	~BaseEnemy();

	void init(ShaderProgram &shaderProgram);
	void update(int deltaTime);

	//virtual int enemyName();

private:
	bool isInFrustrum();
};

