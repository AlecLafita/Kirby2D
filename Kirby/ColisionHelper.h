#pragma once
#include <glm/glm.hpp>

//forward declarations
class TileMap;
class Character;
class Player;
class BaseEnemy;

class ColisionHelper{
public:
	ColisionHelper();
	~ColisionHelper() {}

	//xMoveDir -> Can do a movement to Dir without colliding with x?

	bool mapMoveRight(const TileMap* tMap, Character* character) const;
	bool mapMoveLeft(const TileMap* tMap, Character* character) const;
	bool mapMoveDown(const TileMap* tMap, Character* character) const;
	bool mapMoveUp(const TileMap* tMap, Character* character) const;

	bool characterMoveRight(const Character* characterToCollide, Character* character) const;
	bool characterMoveLeft(const Character* characterToCollide, Character* character) const;
	bool characterMoveUp(const Character* characterToCollide, Character* character) const;
	bool characterMoveDown(const Character* characterToCollide, Character* character) const;

	//Can player swallow character?
	bool playerSwallowCharacter( Player* player, BaseEnemy* enemy)const;


private:
	//Check if two quads intersect, pos is the left-top vertex
	bool quadsCollision(glm::vec2 q1Pos, glm::vec2 q1Size, glm::vec2 q2Pos, glm::vec2 q2Size) const;

	//Returns the euclidean distance between two positions
	int distanceBetweenPositions(const glm::ivec2 pos1, const glm::ivec2 pos2) const;
};

