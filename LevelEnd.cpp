#include "LevelEnd.h"


LevelEnd::LevelEnd(int posX, int posY) {
	Position.x = posX;
	Position.y = posY;
	SizeX = SizeY = 32;

	Type = "level_end";
}


LevelEnd::~LevelEnd(void)
{
}
