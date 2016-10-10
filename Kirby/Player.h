#pragma once
#include "Character.h"
class Player : public Character
{

#define MAX_JUMPS 3

public:
	Player();
	~Player();

	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);

private:
	bool bHoving;
	int nJumps;
};

