#pragma once

#include "../base/Sprite.h"
#include "../base/TileMap.h"

class Scene;

class BaseObject
{
public:
	BaseObject();
	~BaseObject(){}

	void init(ShaderProgram &shaderProgram, Scene* scene);
	void update(int deltaTime);
	void render();

	void setTexturePosition(const glm::fvec2 &pos); //must be called before init
	void setPosition(const glm::vec2 &pos);

protected:
	string mPathToSpritesheet;
	Texture spritesheet;
	Sprite *sprite;
	Scene* mScene;
	glm::fvec2 mTexturePosition;

	int mNumberAnimations;
	glm::ivec2 posObj;

};

