#include "ColisionHelper.h"
#include "../base/TileMap.h"
#include "../characters/Player.h"
#include "../characters/BaseEnemy.h"

#include "../base/Constants.h"

#include <iostream>

using namespace std;


ColisionHelper::ColisionHelper()
{
}

// Collision tests for axis aligned bounding boxes.
// Method collisionMoveDown also corrects Y coordinate if the box is
// already intersecting a tile below.

bool ColisionHelper::mapMoveRight(const TileMap* tMap, Character* character) const {
	glm::ivec2 pos = character->getPosition();
	glm::ivec2 size = character->getSize();

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

bool ColisionHelper::mapMoveLeft(const TileMap* tMap, Character* character) const {
	glm::ivec2 pos = character->getPosition();
	glm::ivec2 size = character->getSize();
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

bool ColisionHelper::mapMoveDown(const TileMap* tMap, Character* character) const {
	glm::ivec2 pos = character->getPosition();
	glm::ivec2 size = character->getSize();

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
			if (pos.y - tileSize * y + size.y <= 4) //4 es FALL_STEP de Player.cpp
			{
				character->setPosition(glm::ivec2(pos.x, tileSize * y - size.y));
				return true;
			}
		}
	}

	return false;
}

bool ColisionHelper::mapMoveUp(const TileMap* tMap, Character* character) const {
	glm::ivec2 pos = character->getPosition();
	glm::ivec2 size = character->getSize();

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


bool ColisionHelper::characterCollidesCharacter(const Character* characterToCollide, Character* character) const {
	glm::ivec2 pos = character->getPosition();
	glm::ivec2 size = character->getSize();
	
	/*
	int right_char = getRightCollisionBox(character);
	int top_char = getTopCollisionBox(character);
	int bottom_char = getBottomCollisionBox(character);

	int left_charToCollide = getLeftCollisionBox(characterToCollide);
	int right_charToCollide = getRightCollisionBox(characterToCollide);
	int top_charToCollide = getTopCollisionBox(characterToCollide);
	int bottom_charToCollide = getBottomCollisionBox(characterToCollide);

	return generalColision(right_char, top_char, bottom_char, left_charToCollide, right_charToCollide,top_charToCollide, bottom_charToCollide);
	*/
	//return quadsCollision(pos, size, characterToCollide->getPosition(), size); //All characters same size??
	bool res = quadsCollision(character->getPosition(), character->getSize(),
		characterToCollide->getPosition(), characterToCollide->getSize());
	if (dynamic_cast<Player*>(character) && res)
		dynamic_cast<Player*>(character)->justDamaged();
	return res;
}

bool ColisionHelper::playerSwallowCharacter(Player* player, BaseEnemy* enemy)const {
	glm::ivec2 playerPos = player->getPosition();
	glm::ivec2 enemyPos = enemy->getPosition();
	if (player->isSwalling() && (distanceBetweenPositions(playerPos, enemyPos) <= SWALLOW_DISTANCE)) {
		//Move character to player
		glm::ivec2 dir = playerPos - enemyPos;
		enemy->setPosition(enemyPos + dir / SWALLOW_VELOCITY_FACTOR);
		if (quadsCollision(playerPos,player->getSize(), enemy->getPosition(), enemy->getSize()))
			return true;
	}
	return false;
}

/*
bool ColisionHelper::generalColision(int right_char, int top_char, int bottom_char,
	int left_charToCollide, int right_charToCollide, int top_charToCollide, int bottom_charToCollide) const {

	return (right_char > left_charToCollide &&  right_char < right_charToCollide && //basic for right collision
		( (top_char < bottom_charToCollide && top_char > top_charToCollide) || //same size, char bottom from charToCollide
		  (bottom_char > top_charToCollide && bottom_char < bottom_charToCollide) || //same size, char up from charToCollide
		  (top_char <= top_charToCollide && bottom_char >= bottom_charToCollide) || //char bigger or equal(surrounding) than charToCollide
		  (top_char > top_charToCollide && bottom_char < bottom_charToCollide) //char smaller(surrounded) than charToCollide
		 ));
}

int ColisionHelper::getLeftCollisionBox(const Character* character) const{
	return character->getPosition().x;
}

int ColisionHelper::getRightCollisionBox(const Character* character) const{
	return character->getPosition().x + character->getPosition().x;
}

int ColisionHelper::getTopCollisionBox(const Character* character) const{
	return character->getPosition().y;
}

int ColisionHelper::getBottomCollisionBox(const Character* character) const{
	return character->getPosition().y + character->getSize().y;
}
*/

bool ColisionHelper::quadsCollision(glm::vec2 q1Pos, glm::vec2 q1Size, glm::vec2 q2Pos, glm::vec2 q2Size) const{
	//It can be divided for the four sides 

	float q1x1 = q1Pos.x; float q1x2 = q1x1 + q1Size.x;
	float q1y1 = q1Pos.y; float q1y2 = q1y1 + q1Size.y;

	float q2x1 = q2Pos.x; float q2x2 = q2x1 + q2Size.x;
	float q2y1 = q2Pos.y; float q2y2 = q2y1 + q2Size.y;

	//http://stackoverflow.com/questions/306316/determine-if-two-rectangles-overlap-each-other

	//if q1 = q2 they will not collide -> useful as we dont want characters to collide with themselves
	return ((q1x1 < q2x2 && q1x2 >=q2x1 && q1y1 < q2y1 && q1y2 > q2y1) || 
		(q2x1 < q1x2 && q2x2 > q1x1 && q2y1 < q1y1 && q2y2 > q1y1));
}


int ColisionHelper::distanceBetweenPositions(const glm::ivec2 pos1, const glm::ivec2 pos2) const{
	return sqrt((pos1.x - pos2.x)*(pos1.x - pos2.x) + (pos1.y - pos2.y)*(pos1.y - pos2.y));
}


