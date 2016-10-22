#pragma once
#include "BaseEnemy.h"

class FlyingDummyEnemy :
	public BaseEnemy
{
public:
	FlyingDummyEnemy();
	~FlyingDummyEnemy(){}

	void init(ShaderProgram &shaderProgram, Scene* scene);
	void update(int deltaTime);

	PowerType getType() const {
		return PowerType::Normal;
	}
private:
	int actY; //how many frames at same y direction
};

