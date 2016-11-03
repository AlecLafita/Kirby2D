#include "EnergyObject.h"
#include "../base/Scene.h"

EnergyObject::EnergyObject()
{
	fullRecovery = false;
	int en = rand() % 9; //number of energy objects
	switch (en) {
	case 0:
		setTexturePosition(glm::fvec2(0.0f, 0.25f));
		break;
	case 1:
		setTexturePosition(glm::fvec2(0.25f, 0.25f));
		break;
	case 2:
		setTexturePosition(glm::fvec2(0.5f, 0.25f));
		break;
	case 3:
		setTexturePosition(glm::fvec2(0.75f, 0.25f));
		break;
	case 4:
		setTexturePosition(glm::fvec2(0.0f, 0.5f));
		break;
	case 5:
		setTexturePosition(glm::fvec2(0.25f, 0.5f));
		break;
	case 6:
		setTexturePosition(glm::fvec2(0.5f, 0.5f));
		break;
	case 7:
		setTexturePosition(glm::fvec2(0.75f, 0.5f));
		break;
	case 8:
		setTexturePosition(glm::fvec2(0.0f, 0.75f));
		break;
	//Add all the case when we have the final items spritesheet
	default:
		break;
	}
}


int EnergyObject::getScore() {
	if (fullRecovery)
		return 150;
	else return 100;
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
