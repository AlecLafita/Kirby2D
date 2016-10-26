#pragma once
#include "BaseObject.h"

class EnergyObject : public BaseObject
{
public:
	EnergyObject();
	~EnergyObject() {}

	void update(int deltaTime);
	
	int getScore();

	void setFullRecovery(bool fullEnergy);
	bool recoversFullEnergy() { return fullRecovery; }

private:
	bool fullRecovery;
};

