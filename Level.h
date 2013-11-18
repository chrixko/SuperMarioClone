#pragma once

#include <vector>
#include <map>

#include "Tile.h"

#define TYPE_COUNT 13
#define TILE_SIZE 32

enum ENTITY_TYPE {
	ENTITY_TYPE_NONE			= 0,
	ENTITY_TYPE_BRICK			= 1,
	ENTITY_TYPE_CRATE			= 2,
	ENTITY_TYPE_COIN			= 3,
	ENTITY_TYPE_CRATE_MUSHROOM	= 4,
	ENTITY_TYPE_BRICK_COINS		= 5,
	ENTITY_TYPE_PIPE_ENTRY		= 6,
	ENTITY_TYPE_GOOMBA			= 7,
	ENTITY_TYPE_KOOPA			= 8,
	ENTITY_TYPE_PIPE_OUT		= 9,
	ENTITY_TYPE_PIPE_IN_VERT	= 10,
	ENTITY_TYPE_FLAG			= 11,
	ENTITY_TYPE_LEVEL_END		= 12,
	ENTITY_TYPE_VINE			= 13
};

class Level {
	public:
		Level(std::string name);
		~Level(void);

		std::string Name;
		
		std::map<int, std::map<int, Tile*>> Map;
		std::map<int, std::map<int, ENTITY_TYPE>> DefinedEntities;
		std::vector<Surface*> Tiles;
		
		float OffsetX;		

		int TileCountX;
		int TileCountY;

		bool Inited;
		void Init();
		void Draw(Surface* screen, float deltaTime);

		void SaveData();
		void LoadData();

		void SaveCollisionMap();
		void LoadCollisionMap();
		void SaveEntityMap();
		void LoadEntityMap();

		void Destroy();

		Tile* GetTile(int posX, int posY);
	private:
		int getNewTileIndex(Surface* tile);
};

