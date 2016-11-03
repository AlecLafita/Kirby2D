#pragma once
#include "BaseObject.h"

class RotationObject : public BaseObject {
public:
	RotationObject();
	~RotationObject() {}

	void init(ShaderProgram &shaderProgram, Scene* scene);
	void update(int deltaTime);

	glm::ivec2 getSize() { return glm::ivec2(BIG_OBJECT_SIZE_X,BIG_OBJECT_SIZE_Y); }

	void setCentralPosChar(glm::ivec2 newPos) {centralPosChar = newPos;}
	void setRadius(float r) {radiusChar =r;}

	void setLeftRotation() {dirRot = -1;}
	void setRightRotation() {dirRot = 1;}


private:
	float angleIncr;
	glm::ivec2 centralPosChar;
	float radiusChar;
	int dirRot;
};

