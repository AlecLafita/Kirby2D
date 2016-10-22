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

	PowerType getType() const {
		return PowerType::Normal;
	}
};

