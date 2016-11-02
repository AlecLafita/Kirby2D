#pragma once
#include "BaseObject.h"

class RotationObject : public BaseObject {
public:
	RotationObject();
	~RotationObject() {}

	void init(ShaderProgram &shaderProgram, Scene* scene);
	void update(int deltaTime);

	glm::ivec2 getSize() { return glm::ivec2(24,7); }

private:
	float angleIncr;
};

