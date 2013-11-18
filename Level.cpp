#include <iostream>
#include <fstream>
#include <sstream>

#include "Assets.h"
#include "Input.h"

#include "Brick.h"

#include "Level.h"

Level::Level(std::string name) {    
	Name = name;
	TileCountX = TileCountY = 0;
	OffsetX = 0;
	Inited = false;
}

Level::~Level(void) {
}

void Level::Init() {
	Inited = true;

	std::string fileName = "assets/levels/" + Name + "/background.png";

	Surface* background = new Surface(&fileName[0]);
	
	TileCountX = ceil(background->GetWidth() / TILE_SIZE);
	TileCountY = ceil(background->GetHeight() / TILE_SIZE);

	for(int x = 0; x < TileCountX; x++) {
		for(int y = 0; y < TileCountY; y++) {
			Surface* pixels = new Surface(TILE_SIZE, TILE_SIZE);
					
			int posX = x * TILE_SIZE;
			int posY = y * TILE_SIZE;

			background->CopyTo(pixels, -posX, -posY);

			int index = getNewTileIndex(pixels);
			
			Map[x][y] = new Tile(x, y, index, Tiles[index]);
		}
	}					

	delete background;

	LoadData();
}

void Level::Draw(Surface* screen, float deltaTime) {
	int startX = floor(OffsetX / TILE_SIZE);	
	int endX = ceil((SCRWIDTH + OffsetX) / TILE_SIZE);

	for(int x = startX; x < endX; x++) {
		for(int y = 0; y < TileCountY; y++) {
			if(Map[x][y] != 0) {
				Map[x][y]->Graphic->CopyTo(screen, (x * TILE_SIZE) - OffsetX, y * TILE_SIZE);
			}			
		}
	}
}

int Level::getNewTileIndex(Surface* tile) {    
	for(int i = 0; i < Tiles.size(); i++) {

		bool sameTile = true;    
		for(int j = 0; j < (TILE_SIZE * TILE_SIZE); j++) {

			Pixel _old = Tiles[i]->GetBuffer()[j];
			Pixel _new = tile->GetBuffer()[j];

			if(_old != _new) {
				sameTile = false;            
				break;
			}           
		}

		if(sameTile) return i;
	}

	Tiles.push_back(tile);

	 return Tiles.size() -1;
}

void Level::SaveCollisionMap() {
	std::ofstream file;
	
	file.open("assets/levels/" + Name + "/collision.txt", std::ios::out | std::ios::trunc);

	if (file.is_open()) {
		for(int x = 0; x < TileCountX; x++) {
			for(int y = 0; y < TileCountY; y++) {						
				file << Map[x][y]->Blocks;
			}
		}			
	} else {
		printf("Error saving collision map\n");
	}

	file.flush();
	file.close();

	printf("Done saving collision map\n");
}

void Level::LoadCollisionMap() {
	printf("Loading collision map\n");

	std::ifstream file("assets/levels/" + Name + "/collision.txt");

	while(file.good()) {			
		for(int x = 0; x < TileCountX; x++) {
			for(int y = 0; y < TileCountY; y++) {                        
				char value = file.get();

				Map[x][y]->Blocks = (value == '1');
			}
		}
		break;
	}

	file.close();

	printf("Done loading collision map\n");
}

void Level::SaveData() {
	SaveCollisionMap();
	SaveEntityMap();
}

void Level::LoadData() {
	LoadCollisionMap();
	LoadEntityMap();
}

void Level::SaveEntityMap() {
	std::ofstream file;
	
	file.open("assets/levels/" + Name + "/entities.txt", std::ios::out | std::ios::trunc);

	if (file.is_open()) {
		for(int x = 0; x < TileCountX; x++) {
			for(int y = 0; y < TileCountY; y++) {
				if(DefinedEntities[x][y] != 0) {
					file << x << "," << y << "," << (int)DefinedEntities[x][y] << "\n";
				}				
			}
		}			
	} else {
		printf("Error saving entity map\n");
	}

	file.flush();
	file.close();

	printf("Done saving entity map\n");
}

void Level::LoadEntityMap() {
	std::ifstream file("assets/levels/" + Name + "/entities.txt");

	while(file.good()) {
		for(std::string line; getline(file,line);) {
			
			std::istringstream sLine(line);

			std::string data[3];
			for(int i = 0; i < 3; i++) {
				getline(sLine, data[i], ',');
			}
			
			//Haha what
			DefinedEntities[std::atoi(&(data[0])[0])][std::atoi(&(data[1])[0])] = (ENTITY_TYPE)std::atoi(&(data[2])[0]);
		}
	}

	printf("Done loading entity map\n");
}

void Level::Destroy() {

}

Tile* Level::GetTile(int posX, int posY) {
	return Map[posX / TILE_SIZE][posY / TILE_SIZE];
}