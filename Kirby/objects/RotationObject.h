#pragma once
#include "BaseObject.h"

class RotationObject : public BaseObject {
public:
	RotationObject();
	~RotationObject() {}

	void init(ShaderProgram &shaderProgram, Scene* scene);
	void update(int deltaTime);

	glm::ivec2 getSize() { return glm::ivec2(24,7); }

	void setCentralPosChar(glm::ivec2 newPos) {centralPosChar = newPos;}
	void setRadius(float r) {radiusChar =r;}

private:
	float angleIncr;
	glm::ivec2 centralPosChar;
	float radiusChar;
};

