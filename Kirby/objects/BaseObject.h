#pragma once

#include "../base/Sprite.h"
#include "../base/TileMap.h"
#include "../base/Defines.h"

class Scene;

enum ObjectAnimations {
	LEFT,RIGHT
};

class BaseObject
{
public:
	BaseObject();
	~BaseObject(){}

	virtual void init(ShaderProgram &shaderProgram, Scene* scene);
	virtual void update(int deltaTime);
	void render();

	virtual int getScore() { return 0; }

	void setPathToSpriteSheet(string pathToSpriteSheet); //must be called before init

	void setTexturePosition(const glm::fvec2 &pos); //must be called before init
	void setPosition(const glm::ivec2 &pos);

	glm::ivec2 getPosition() { return posObj; }
	virtual glm::ivec2 getSize() { return glm::ivec2(OBJECT_SIZE_X,OBJECT_SIZE_Y); }

	bool isTaken() { return bTaken; }
	void forceNotIsTook () {bTaken=false;}

	void setLeftAnimation();
	void setRightAnimation();

	glm::ivec2 getSize() const { return glm::ivec2(OBJECT_SIZE_X, OBJECT_SIZE_Y); }


protected:
	string mPathToSpritesheet;
	Texture spritesheet;
	Sprite *sprite;
	Scene* mScene;
	glm::fvec2 mTexturePosition;

	bool bTaken; //Object has been taken, make it dissapear on the next frames
	int mNumberAnimations;
	glm::ivec2 posObj;
	float sizeInSpriteSheetX, sizeInSpriteSheetY;

	int START_ROW_LEFT;
	int START_ROW_RIGHT;

};

