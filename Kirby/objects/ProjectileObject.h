#pragma once
#include "BaseObject.h"
class ProjectileObject : public BaseObject
{
public:
	ProjectileObject();
	~ProjectileObject() {}

	void init(ShaderProgram &shaderProgram, Scene* scene);
	void update(int deltaTime);
	void setDirection(glm::fvec2 dir);

	glm::ivec2 getSize() { return glm::ivec2(24,7); }

private:
	glm::fvec2 dir;

};

