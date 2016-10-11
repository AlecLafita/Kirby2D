#include "ProjectileObject.h"


ProjectileObject::ProjectileObject()
{
	//mNumberAnimations = 1;
}

void ProjectileObject::update(int deltaTime) {
	posObj += dir;
	//TODO COLLISIONS
	BaseObject::update(deltaTime);
}

void ProjectileObject::setDirection(glm::fvec2 dir) {
	this->dir = dir;
}
