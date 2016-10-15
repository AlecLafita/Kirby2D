#include "ColisionHelper.h"
#include "TileMap.h"
#include "Player.h"

#include <iostream>
using namespace std;


#define SWALLOW_DISTANCE 50 //How far can Kirby swallow
#define SWALLOW_VELOCITY_FACTOR 40

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


bool ColisionHelper::characterMoveRight(const Character* character, const glm::ivec2 &pos, const glm::ivec2 &size) const {
	return quadsCollision(pos, size, character->getPosition(), size); //All characters same size??
}
bool ColisionHelper::characterMoveLeft(const Character* character, const glm::ivec2 &pos, const glm::ivec2 &size) const{
	return quadsCollision(pos, size, character->getPosition(), size); //All characters same size??
}
bool ColisionHelper::characterMoveUp(const Character* character, const glm::ivec2 &pos, const glm::ivec2 &size) const {
	return quadsCollision(pos, size, character->getPosition(), size); //All characters same size??
}
bool ColisionHelper::characterMoveDown(const Character* character, const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) const {
	bool res = quadsCollision(pos, size, character->getPosition(), size); //All characters same size??
	if (res) {
		*posY = character->getPosition().y - size.y;
		return true;
	}
	return false;
}

bool ColisionHelper::playerSwallowCharacter(const Player* player, glm::ivec2 &pos)const {
	glm::ivec2 playerPos = player->getPosition();
	if (player->isSwalling() && (distanceBetweenPositions(playerPos,pos) <= SWALLOW_DISTANCE)) {
		//Move character to player
		glm::ivec2 dir = playerPos - pos;
		pos += dir / SWALLOW_VELOCITY_FACTOR;
		return true;
	}
	else return false;
}

bool ColisionHelper::quadsCollision(glm::vec2 q1Pos, glm::vec2 q1Size, glm::vec2 q2Pos, glm::vec2 q2Size) const{
	//It can be divided for the four sides 

	float q1x1 = q1Pos.x; float q1x2 = q1x1 + q1Size.x;
	float q1y1 = q1Pos.y; float q1y2 = q1y1 + q1Size.y;

	float q2x1 = q2Pos.x; float q2x2 = q2x1 + q2Size.x;
	float q2y1 = q2Pos.y; float q2y2 = q2y1 + q2Size.y;

	//http://stackoverflow.com/questions/306316/determine-if-two-rectangles-overlap-each-other

	return ((q1x1 < q2x2 && q1x2 >=q2x1 && q1y1 < q2y1 && q1y2 > q2y1) || 
		(q2x1 < q1x2 && q2x2 > q1x1 && q2y1 < q1y1 && q2y2 > q1y1));
}

int ColisionHelper::distanceBetweenPositions(const glm::ivec2 pos1, const glm::ivec2 pos2) const{
	return sqrt((pos1.x - pos2.x)*(pos1.x - pos2.x) + (pos1.y - pos2.y)*(pos1.y - pos2.y));
}


