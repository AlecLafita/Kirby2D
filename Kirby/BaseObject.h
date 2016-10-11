#pragma once

#include "Sprite.h"
#include "TileMap.h"


class BaseObject
{
public:
	BaseObject();
	~BaseObject(){}

	void init(ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap *tileMap);
	void setPathToSpriteSheet(string pathToSpriteSheet); //must be called before init
	void setTexturePosition(const glm::fvec2 &pos); //must be called before init
	void setPosition(const glm::vec2 &pos);

protected:
	string mPathToSpritesheet;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
	glm::fvec2 mTexturePosition;

	int mNumberAnimations;
	glm::ivec2 posObj;

};

