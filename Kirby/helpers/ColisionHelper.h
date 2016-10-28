#pragma once
#include <glm/glm.hpp>

//forward declarations
class TileMap;
class Character;
class Player;
class BaseEnemy;
class BaseObject;

class ColisionHelper{
public:
	ColisionHelper();
	~ColisionHelper() {}

	//(second parameter) collides with (first parameter) by going to certain direction? The one who's moving is the econd parameter

	bool mapMoveRight(const TileMap* tMap, Character* character) const;
	bool mapMoveLeft(const TileMap* tMap, Character* character) const;
	bool mapMoveDown(const TileMap* tMap, Character* character) const;
	bool mapMoveUp(const TileMap* tMap, Character* character) const;

	//If enemy are near a precipice
	bool mapFalls(const TileMap* map, BaseEnemy* enemy);

	//The second parameter is the one checking collisions
	bool characterCollidesCharacter(const Character* characterToCollide, Character* character) const;

	//Can player swallow character?
	bool playerSwallowCharacter( Player* player, BaseEnemy* enemy)const;

	//Does the character collides with an item?
	bool characterCollidesObject(Character* character, BaseObject* object) const;

private:
	//Check if two quads intersect, pos is the left-top vertex
	bool quadsCollision(glm::vec2 q1Pos, glm::vec2 q1Size, glm::vec2 q2Pos, glm::vec2 q2Size) const;
	
	//Returns the euclidean distance between two positions
	int distanceBetweenPositions(const glm::ivec2 pos1, const glm::ivec2 pos2) const;

	//Returns if two caharacters are (near to be) at same horizontal line, used for kirby swalling
	bool sameHorizontal(const glm::ivec2 pos1, const glm::ivec2 pos2) const;
};

