#pragma once
#include "BaseEnemy.h"
class WalkingDummyEnemy :
	public BaseEnemy
{
public:
	WalkingDummyEnemy();
	~WalkingDummyEnemy() {}

	void init(ShaderProgram &shaderProgram, Scene* scene);
	void update(int deltaTime);

protected :
	void searchPlayer(); //See if player is near, in this case, change X direction aiming to follow him
};

