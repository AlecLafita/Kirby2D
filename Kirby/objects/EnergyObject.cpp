#include "EnergyObject.h"
#include "../base/Scene.h"

EnergyObject::EnergyObject()
{
	fullRecovery = false;
	int en = rand() % 2; //number of energy objects
	switch (en) {
	case 0:
		setTexturePosition(glm::fvec2(0.25f, 0.25f));
		break;
	case 1:
		setTexturePosition(glm::fvec2(0.0f, 0.25f));
		break;
	//Add all the case when we have the final items spritesheet
	default:
		break;
	}
}

void EnergyObject::update(int deltaTime) {
	//if(isInfrustrum())
	if (mScene->playerTakesItem(this)) bTaken = true;
	BaseObject::update(deltaTime);
}

void EnergyObject::setFullRecovery(bool fullEnergy) {
	this->fullRecovery = fullEnergy;
	if (fullEnergy) //reassign spritesheet to tomato
		setTexturePosition(glm::fvec2(0.0f, 0.0f));
}
