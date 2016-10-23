#pragma once
#include "BaseObject.h"

class LifeObject : public BaseObject
{
public:
	LifeObject();
	~LifeObject() {}

	void update(int deltaTime);

};

