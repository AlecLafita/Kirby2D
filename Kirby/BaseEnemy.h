#pragma once
#include "Character.h"

class BaseEnemy : public Character
{

public:
	BaseEnemy();
	~BaseEnemy();

	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);

private:
	bool isInFrustrum();
};

