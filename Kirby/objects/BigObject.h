#pragma once
#include "BaseObject.h"


class BigObject : public BaseObject
{
public:
	BigObject();
	~BigObject(){}

	void init(ShaderProgram &shaderProgram, Scene* scene);

	glm::ivec2 getSize() { return glm::ivec2(BIG_OBJECT_SIZE_X, BIG_OBJECT_SIZE_Y); }

};

