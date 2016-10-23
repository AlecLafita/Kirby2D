#include "LifeObject.h"
#include "../base/Scene.h"

LifeObject::LifeObject()
{
	setTexturePosition(glm::fvec2(0.75f,0.0f)); //Position on texture of kirby life
}


void LifeObject::update(int deltaTime) {
	//if(isInfrustrum())
	if (mScene->playerTakesItem(this)) bTaken = true;
	BaseObject::update(deltaTime);
}


