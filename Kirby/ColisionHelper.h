#pragma once
#include "TileMap.h"

class ColisionHelper{
public:
	ColisionHelper();
	~ColisionHelper() {}

	bool mapMoveRight(const TileMap* tMap, const glm::ivec2 &pos, const glm::ivec2 &size) const;
	bool mapMoveLeft(const TileMap* tMap, const glm::ivec2 &pos, const glm::ivec2 &size) const;
	bool mapMoveDown(const TileMap* tMap, const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) const;
	bool mapMoveUp(const TileMap* tMap, const glm::ivec2 &pos, const glm::ivec2 &size) const;


};

