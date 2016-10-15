#pragma once
#include <glm/glm.hpp>


class TileMap;
class Character;

class ColisionHelper{
public:
	ColisionHelper();
	~ColisionHelper() {}


	//xMoveDir -> Can do a movement to Dir without colliding with x?

	bool mapMoveRight(const TileMap* tMap, const glm::ivec2 &pos, const glm::ivec2 &size) const;
	bool mapMoveLeft(const TileMap* tMap, const glm::ivec2 &pos, const glm::ivec2 &size) const;
	bool mapMoveDown(const TileMap* tMap, const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) const;
	bool mapMoveUp(const TileMap* tMap, const glm::ivec2 &pos, const glm::ivec2 &size) const;

	bool characterMoveRight(const Character* character, const glm::ivec2 &pos, const glm::ivec2 &size) const;
	bool characterMoveLeft(const Character* character, const glm::ivec2 &pos, const glm::ivec2 &size) const;
	bool characterMoveUp(const Character* character, const glm::ivec2 &pos, const glm::ivec2 &size) const;
	bool characterMoveDown(const Character* character, const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) const;


private:
	//Check if two quads intersect, pos is the left-top vertex
	bool quadsCollision(glm::vec2 q1Pos, glm::vec2 q1Size, glm::vec2 q2Pos, glm::vec2 q2Size) const;
};

