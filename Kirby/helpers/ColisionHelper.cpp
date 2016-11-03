#include "ColisionHelper.h"
#include "../base/TileMap.h"
#include "../characters/Player.h"
#include "../characters/BaseEnemy.h"
#include "../objects/PortalObject.h"

#include "../characters/IceKirby.h"
#include "../characters/IcyEnemy.h"

#include "../base/Defines.h"

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
			if (pos.y - tileSize * y + size.y <= FALL_STEP) {
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
		if (map[y*mapTilesWidth + x] != 0) {
			return true;
		}
	}
	return false;
}

bool ColisionHelper::mapFalls(const TileMap* tMap, BaseEnemy* enemy) {
	glm::ivec2 pos = enemy->getPosition();
	glm::ivec2 size = enemy->getSize();

	int x0, x1, y;
	int tileSize = tMap->getTileSize();

	x0 = pos.x / tileSize;
	x1 = (pos.x + size.x - 1) / tileSize;
	y = (pos.y + size.y + 1) / tileSize;
	int mapTilesWidth = tMap->getMapTilesWidth();
	int* map = tMap->getMap();
	for (int x = x0; x <= x1; x++) {
		if (map[y*mapTilesWidth + x] == 0){
			return true;
		}
	}

	return false;
}



bool ColisionHelper::characterCollidesCharacter(const Character* characterToCollide, Character* character) const {
	return quadsCollision(character->getCollisionPosition(), character->getCollisionSize(),
		characterToCollide->getCollisionPosition(), characterToCollide->getCollisionSize());
}

bool ColisionHelper::playerSwallowObject( Player* player, BaseObject* obj) const{

	glm::ivec2 playerPos = player->getPosition();
	glm::ivec2 objPos = obj->getPosition();

	int diffInX = (playerPos.x - objPos.x);
	if (player->isSwalling()
		&& (distanceBetweenPositions(playerPos, objPos) <= SWALLOW_DISTANCE)
		&& sameHorizontal(playerPos, objPos)
		&& (( diffInX > 0 && player->isLeftDirection()) || ( diffInX < 0 && !player->isLeftDirection()))
			) {

		//Move obj to player
		glm::ivec2 dir = playerPos - objPos;
		obj->setPosition(objPos + dir / SWALLOW_VELOCITY_FACTOR);
		if (quadsCollision(playerPos,player->getSize(), obj->getPosition(), obj->getSize()))
			return true;
	}
	return false;
}

bool ColisionHelper::playerSwallowCharacter(Player* player, BaseEnemy* enemy)const {
	glm::ivec2 playerPos = player->getPosition();
	glm::ivec2 enemyPos = enemy->getPosition();
	int diffInX = (playerPos.x - enemyPos.x);
	if (player->isSwalling()
		&& (distanceBetweenPositions(playerPos, enemyPos) <= SWALLOW_DISTANCE)
		&& sameHorizontal(playerPos, enemyPos)
			&& (( diffInX > 0 && player->isLeftDirection()) || ( diffInX < 0 && !player->isLeftDirection()))
			) {

		//Move character to player
		glm::ivec2 dir = playerPos - enemyPos;
		enemy->setPosition(enemyPos + dir / SWALLOW_VELOCITY_FACTOR);
		if (quadsCollision(playerPos,player->getSize(), enemy->getPosition(), enemy->getSize()))
			return true;
	}
	return false;
}

bool ColisionHelper::characterCollidesObject(Character* character, BaseObject* object) const{
	return quadsCollision(character->getCollisionPosition(), character->getCollisionSize(), object->getPosition(), object->getSize());
}

void ColisionHelper::characterDoesTeleport(Character* character, PortalObject* portalAct, PortalObject* portalDest) const {
	if (characterCollidesObject(character, portalAct) && (character->getNoPortal() == 0)) {
		character->setNoPortal(PORTAL_WAITING_TIME);
		glm::ivec2 newPos= portalDest->getPosition();

		glm::ivec2 diff = character->getPosition() - portalAct->getPosition();
		newPos.y += diff.y;
		
		if (diff.x > 0 ) //Character at left side
			newPos.x -= character->getSize().x;
		else 
			newPos.x += portalAct->getSize().x;

		character->setPosition(newPos);

		int diffStartY = character->getStartY() - portalAct->getPosition().y;
		character->setStartY(portalDest->getPosition().y + diffStartY);
	}

	//Check if object associated to character can also be teleported
	if (IceKirby *iKirby = dynamic_cast<IceKirby*>(character)) {
		glm::ivec2 newObjPos = portalDest->getPosition();
		ProjectileObject* obj = iKirby->getIce();
		if (quadsCollision(obj->getPosition(),obj->getSize(),portalAct->getPosition(),portalAct->getSize())) {
			glm::ivec2 diffObj = obj->getPosition() - portalAct->getPosition();
			glm::ivec2 diffChar = character->getPosition() - portalAct->getPosition();
			newObjPos.y += diffObj.y;
			
			if (diffChar.x > 0 ) //Character at left side
				newObjPos.x -= obj->getSize().x;
			else 
				newObjPos.x += portalAct->getSize().x;

			obj->setPosition(newObjPos);
		}
	}

}

bool ColisionHelper::mapCollidesObject(const TileMap* tMap, BaseObject* object)const{
	glm::ivec2 pos = object->getPosition();
	glm::ivec2 size = object->getSize();
	int x0, x1, y0, y1;
	int tileSize = tMap->getTileSize();

	x0 = pos.x / tileSize;
	x1 = (pos.x + size.x - 1) / tileSize;
	y0 = pos.y / tileSize;
	y1 = (pos.y + size.y - 1) / tileSize;
	int mapTilesWidth = tMap->getMapTilesWidth();
	int* map = tMap->getMap();
	for (int x = x0; x <= x1; x++){
		for (int y = y0; y <= y1; y++) {
			if (map[y*mapTilesWidth + x] != 0) {
				return true;
			}
		}
	}
	return false;
}

bool ColisionHelper::quadsCollision(glm::vec2 q1Pos, glm::vec2 q1Size, glm::vec2 q2Pos, glm::vec2 q2Size) const{
	//It can be divided for the four sides 

	float q1x1 = q1Pos.x; float q1x2 = q1x1 + q1Size.x;
	float q1y1 = q1Pos.y; float q1y2 = q1y1 + q1Size.y;

	float q2x1 = q2Pos.x; float q2x2 = q2x1 + q2Size.x;
	float q2y1 = q2Pos.y; float q2y2 = q2y1 + q2Size.y;

	if (q1Pos == q2Pos) return false; //Collision with itself

	return ((q1x1 < q2x2 && q1x2 >q2x1 && q1y1 <= q2y1 && q1y2 >= q2y1) || 
		(q2x1 < q1x2 && q2x2 > q1x1 && q2y1 <= q1y1 && q2y2 >= q1y1));
}


int ColisionHelper::distanceBetweenPositions(const glm::ivec2 pos1, const glm::ivec2 pos2) const{
	return sqrt((pos1.x - pos2.x)*(pos1.x - pos2.x) + (pos1.y - pos2.y)*(pos1.y - pos2.y));
}


bool ColisionHelper::sameHorizontal(const glm::ivec2 pos1, const glm::ivec2 pos2) const{
	return abs(pos1.y - pos2.y) < SWALLOW_Y_MAX_DISTANCE;
}

