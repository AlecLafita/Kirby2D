#pragma once
#include "BaseObject.h"

enum ObjectAnimations {
	LEFT,RIGHT
};

class BigObject : public BaseObject
{
public:
	BigObject();
	~BigObject(){}

	void init(ShaderProgram &shaderProgram, Scene* scene);

	void setLeftAnimation();
	void setRightAnimation();
	glm::ivec2 getSize() { return glm::ivec2(BIG_OBJECT_SIZE_X, BIG_OBJECT_SIZE_Y); }

protected:
	int START_ROW_LEFT;
	int START_ROW_RIGHT;
};

