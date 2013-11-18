#include "Input.h"
#include "Assets.h"
#include "SceneManager.h"
#include "LevelSelectionScene.h"


#include "EditorScene.h"

EditorScene::EditorScene(Level* level) : Scene() {
	CurrentLevel = level;
	CurrentType = ENTITY_TYPE_NONE;
}

EditorScene::~EditorScene(void){
}

void EditorScene::Init() {

}

void EditorScene::Update(float deltaTime) {
	Scene::Update(deltaTime);

	if(Input::IsKeyJustPressed(SDLK_LEFT)) {
		if(CurrentLevel->OffsetX > 0) {
			CurrentLevel->OffsetX -= SCRWIDTH;
		}		
	}

	if(Input::IsKeyJustPressed(SDLK_RIGHT)) {
		if(CurrentLevel->OffsetX < (CurrentLevel->TileCountX * TILE_SIZE) - SCRWIDTH) {
			CurrentLevel->OffsetX += SCRWIDTH;
		}		
	}

	if(Input::IsKeyJustPressed(SDLK_KP_PLUS) && (int)CurrentType < TYPE_COUNT) {
		CurrentType = (ENTITY_TYPE)((int)CurrentType + 1);
	}

	if(Input::IsKeyJustPressed(SDLK_KP_MINUS) && (int)CurrentType > 0) {
		CurrentType = (ENTITY_TYPE)((int)CurrentType - 1);
	}

	int tileX = (Input::State->MouseX + CurrentLevel->OffsetX) / TILE_SIZE;
	int tileY = (Input::State->MouseY / TILE_SIZE);

	Tile* selected =  CurrentLevel->Map[tileX][tileY];
	if(selected == 0) return;

	//Only do collision stuff if now entityItem is selected
	if(CurrentType == ENTITY_TYPE_NONE) {
		if(Input::IsMouseJustDown(MOUSE_LEFT)) {
			SetBlockValueFor(selected->GraphicIndex, true);   
			CurrentLevel->SaveCollisionMap();
		}
		if(Input::IsMouseJustDown(MOUSE_RIGHT)) {
			SetBlockValueFor(selected->GraphicIndex, false);
			CurrentLevel->SaveCollisionMap();
		}
	} else {
		if(Input::IsMouseJustDown(MOUSE_LEFT)) {
			CurrentLevel->DefinedEntities[tileX][tileY] = CurrentType;
			CurrentLevel->SaveEntityMap();
        } else if(Input::IsMouseJustDown(MOUSE_RIGHT)) {
            CurrentLevel->DefinedEntities[tileX][tileY] = ENTITY_TYPE_NONE;
			CurrentLevel->SaveEntityMap();
        }
	}

	if(Input::IsKeyJustPressed(SDLK_ESCAPE)) {
		Manager->SwitchScene(new LevelSelectionScene());
	}
}

void EditorScene::Draw(Surface* screen, float deltaTime) {
	CurrentLevel->Draw(screen, deltaTime);

	int startX = floor(CurrentLevel->OffsetX / TILE_SIZE);	
	int endX = ceil((SCRWIDTH + CurrentLevel->OffsetX) / TILE_SIZE);

	for(int x = startX; x < endX; x++) {
		for(int y = 0; y < CurrentLevel->TileCountY; y++) {
			int posX = (x * TILE_SIZE) - CurrentLevel->OffsetX;
			int posY = y * TILE_SIZE;

			int color = CurrentLevel->Map[x][y]->Blocks ? 0xFF0000 : 0x00FF00;  			
			screen->Box(posX, posY, posX + TILE_SIZE, posY + TILE_SIZE, color);

			if(CurrentLevel->DefinedEntities[x][y] != 0) {
				Assets::Graphics["editor_" + std::to_string(CurrentLevel->DefinedEntities[x][y])]->CopyTo(screen, posX, posY);
			}
		}
	}

	int tileX = (Input::State->MouseX + CurrentLevel->OffsetX) / TILE_SIZE;
	int tileY = (Input::State->MouseY / TILE_SIZE);

	Tile* selected = CurrentLevel->Map[tileX][tileY];

	if(selected != 0 && CurrentType != ENTITY_TYPE_NONE) {
		std::string file = "editor_" + std::to_string((int)CurrentType);
		Assets::Graphics[file]->CopyTo(screen, (tileX * TILE_SIZE) - CurrentLevel->OffsetX, (tileY * TILE_SIZE));
	}

	Scene::Draw(screen, deltaTime);
}

void EditorScene::SetBlockValueFor(int tileIndex, bool value) {
	for(int x = 0; x < CurrentLevel->TileCountX; x++) {
		for(int y = 0; y < CurrentLevel->TileCountY; y++) {
			if(CurrentLevel->Map[x][y]->GraphicIndex == tileIndex) {
				CurrentLevel->Map[x][y]->Blocks = value;
			}                    
		}
	}
}