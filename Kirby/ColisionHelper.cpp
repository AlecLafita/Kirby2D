#include "ColisionHelper.h"

#include <iostream>
using namespace std;

ColisionHelper::ColisionHelper()
{
}


// Collision tests for axis aligned bounding boxes.
// Method collisionMoveDown also corrects Y coordinate if the box is
// already intersecting a tile below.

bool ColisionHelper::mapMoveRight(const TileMap* tMap, const glm::ivec2 &pos, const glm::ivec2 &size) const {
	//RIGHT LIMITS, depends on level size
	if ((pos.x + size.x) > (tMap->getMapWidth())) return true;
	int tileSize = tMap->getTileSize();
	int x, y0, y1;
	x = (pos.x + size.x - 1) / tileSize;
	y0 = pos.y / tileSize;
	y1 = (pos.y + size.y - 1) / tileSize;
	int mapTilesWidth = tMap->getMapTilesWidth();
	int* map = tMap->getMap();
	for (int y = y0; y <= y1; y++)
	{
		if (map[y*mapTilesWidth + x] != 0)
			return true;
	}

	return false;
}
bool ColisionHelper::mapMoveLeft(const TileMap* tMap, const glm::ivec2 &pos, const glm::ivec2 &size) const {
	if (pos.x < 0) return true; //Screen limit
	int x, y0, y1;
	int tileSize = tMap->getTileSize();
	x = pos.x / tileSize;
	y0 = pos.y / tileSize;
	y1 = (pos.y + size.y - 1) / tileSize;
	int mapTilesWidth = tMap->getMapTilesWidth();
	int* map = tMap->getMap();
	for (int y = y0; y <= y1; y++)
	{
		if (map[y*mapTilesWidth + x] != 0)
			return true;
	}

	return false;
}
bool ColisionHelper::mapMoveDown(const TileMap* tMap, const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) const {
	int x0, x1, y;
	int tileSize = tMap->getTileSize();

	x0 = pos.x / tileSize;
	x1 = (pos.x + size.x - 1) / tileSize;
	y = (pos.y + size.y - 1) / tileSize;
	int mapTilesWidth = tMap->getMapTilesWidth();
	int* map = tMap->getMap();
	for (int x = x0; x <= x1; x++)
	{
		if (map[y*mapTilesWidth + x] != 0)
		{
			if (*posY - tileSize * y + size.y <= 4) //4 es FALL_STEP de Player.cpp
			{
				*posY = tileSize * y - size.y;
				return true;
			}
		}
	}

	return false;
}
bool ColisionHelper::mapMoveUp(const TileMap* tMap, const glm::ivec2 &pos, const glm::ivec2 &size) const {
	if (pos.y < 0) return true; //Screen limit
	int x0, x1, y;
	int tileSize = tMap->getTileSize();

	x0 = pos.x / tileSize;
	x1 = (pos.x + size.x - 1) / tileSize;
	y = pos.y / tileSize;
	int mapTilesWidth = tMap->getMapTilesWidth();
	int* map = tMap->getMap();
	for (int x = x0; x <= x1; x++)
	{
		if (map[y*mapTilesWidth + x] != 0)
		{
			return true;

		}
	}
	return false;
}