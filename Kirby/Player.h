#pragma once
#include "Character.h"
class Player : public Character
{

#define MAX_JUMPS 3

public:
	Player();
	~Player();

	void computeNextMove();
	void computeJumping();
	void init(ShaderProgram &shaderProgram, Scene* scene);
	void update(int deltaTime);

	bool isSwalling() const;

private:
	bool bHoving;
	int nJumps;
};

