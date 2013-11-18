#include "Assets.h"
#include "Input.h"
#include "SceneManager.h"
#include "MenuScene.h"

#include "Brick.h"
#include "CoinCrate.h"
#include "MushroomCrate.h"
#include "Mushroom.h"
#include "Goomba.h"
#include "Koopa.h"
#include "CoinBrick.h"
#include "PipeIn.h"
#include "PipeOut.h"
#include "Flag.h"
#include "LevelEnd.h"
#include "Coin.h"
#include "VineBrick.h"

#include "GameScene.h"


GameScene::GameScene(void) {
	CurrentLevel = 0;
	CurrentPlayer = 0;
	CurrentCamera = 0;
	Time = 400;
	CurrentLevel = Assets::Levels["1"];
}

GameScene::GameScene(Player* player, std::string level) {
	GameScene::GameScene();
	Time = 400;
	CurrentLevel = Assets::Levels[level];
	CurrentPlayer = player;
	player->Scene = this;
}

GameScene::~GameScene(void) {
}

void GameScene::Init() {
	InitCurrentLevel();

	if(CurrentPlayer == 0) {
		CurrentPlayer = new Player();
	}

	CurrentPlayer->Position.x = 32;
	CurrentPlayer->Position.y = 300;
	AddEntity(CurrentPlayer);

	CurrentCamera = new CameraEntity();
	AddEntity(CurrentCamera);

	switchToNextLevelFlag = switchToSubLevelFlag = false;
}

void GameScene::Update(float deltaTime) {
	if(CurrentPlayer == 0) {
		Scene::Update(deltaTime);
	} else {
		
		if(CurrentPlayer->State != PLAYER_STATE_DEFAULT && CurrentPlayer->State != PLAYER_STATE_ON_FLAG && CurrentPlayer->State != PLAYER_STATE_ON_VINE) {
			CurrentPlayer->Update(deltaTime);
			if(CurrentPlayer->Position.y > SCRHEIGHT + 50) {
				CurrentPlayer->Die();
			}
		} else {
			//Only update entities that are near the player and remove entities that are behind the screen
			if(CurrentPlayer->State != PLAYER_STATE_ON_FLAG || CurrentPlayer->State != PLAYER_STATE_GO_TO_FINISH) {
				Time -= deltaTime;
			}
			
			if(Entities.size() > 0) {
				for(int i = Entities.size() -1; i >= 0; i--) {
					Entity* ent = Entities[i];
					if(ent != 0) {

						if(ent->Position.x < CurrentPlayer->Position.x + SCRWIDTH || strcmp(ent->Type, "camera") == 0) {
							ent->Update(deltaTime);
						}
					
						if(ent->Position.x < CurrentPlayer->Position.x - 300 && strcmp(ent->Type, "camera") != 0) {
							RemoveEntity(ent);
						}

						if(ent->Position.y > SCRHEIGHT + 50) {
							((GravityEntity*)ent)->Die();
						}					
					}			
				}

				if(CurrentPlayer->State != PLAYER_STATE_ON_FLAG || CurrentPlayer->State != PLAYER_STATE_GO_TO_FINISH) {
					CurrentPlayer->State == PLAYER_STATE_DYING;
				}
			}
		}
	}

	CurrentLevel->OffsetX = Camera.x;

	if(Input::IsKeyJustPressed(SDLK_ESCAPE)) {		
		Manager->SwitchScene(new MenuScene());		
		//Assets::DestroyLevels();
	}

	if(switchToSubLevelFlag) {
		switchToSubLevelFlag = false;
		switchToSubLevel();
	}

	if(switchToNextLevelFlag) {
		switchToNextLevelFlag = false;
		switchToNextLevel();
	}
}

void GameScene::FixedUpdate(float deltaTime) {
	if(CurrentPlayer == 0) {
		Scene::FixedUpdate(deltaTime);
	} else {
		
		if(CurrentPlayer->State != PLAYER_STATE_DEFAULT) {
			CurrentPlayer->FixedUpdate(deltaTime);
		} else {
			//Only update entities that are near the player and remove entities that are behind the screen
			if(Entities.size() > 0) {
				for(int i = Entities.size() -1; i >= 0; i--) {
					Entity* ent = Entities[i];
					if(ent != 0) {				
						if(ent->Position.x < CurrentPlayer->Position.x + SCRWIDTH) {
							ent->FixedUpdate(deltaTime);
						}									
					}			
				}
			}
		}
	}
}

void GameScene::Draw(Surface* screen, float deltaTime) {
	CurrentLevel->Draw(screen, deltaTime);

	Scene::Draw(screen, deltaTime);
}

void GameScene::SwitchLevel(std::string name, bool isSubLevel, bool placePlayerAtTubeOut) {
	CurrentPlayer->Position.x = 32;
	CurrentPlayer->Position.y = isSubLevel ? 32 : 300;		
	CurrentPlayer->Velocity.x = 0;
	CurrentCamera->Position.x = CurrentPlayer->Position.x - CurrentPlayer->SizeX;	
	CurrentCamera->SizeX = isSubLevel ? SCRWIDTH : 200;

	if(isSubLevel) {
		Camera.x = 0;
	}

	for(int i = 0; i < Entities.size(); i++) {
		if(strcmp(Entities[i]->Type, "player") != 0 && strcmp(Entities[i]->Type, "camera") != 0) {
			RemoveEntity(Entities[i]);
		}
	}

	freeEntities();	
	Entities.clear();
	Entities.push_back(CurrentPlayer);
	Entities.push_back(CurrentCamera);

	CurrentLevel = Assets::Levels[name];

	InitCurrentLevel();

	if(placePlayerAtTubeOut) {
		for(int i = 0; i < Entities.size(); i++) {
			if(strcmp(Entities[i]->Type, "tube_out") == 0) {
				CurrentPlayer->Position.x = Entities[i]->Position.x + 5;
				CurrentPlayer->Position.y = Entities[i]->Position.y - CurrentPlayer->SizeY - 1;
				break;
			}
		}
	}
}

void GameScene::InitCurrentLevel() {
	for(int x = 0; x < CurrentLevel->TileCountX; x++) {
		for(int y = 0; y < CurrentLevel->TileCountY; y++) {
			if(CurrentLevel->DefinedEntities[x][y] != 0) {
				int posX = x * TILE_SIZE;
				int posY = y * TILE_SIZE;

				switch (CurrentLevel->DefinedEntities[x][y]) {
					case ENTITY_TYPE_BRICK:						
						AddEntity(new Brick(posX, posY));
						break;
					case ENTITY_TYPE_BRICK_COINS:
						AddEntity(new CoinBrick(posX, posY));
						break;
					case ENTITY_TYPE_CRATE:
						AddEntity(new CoinCrate(posX, posY));
						break;
					case ENTITY_TYPE_CRATE_MUSHROOM:
						AddEntity(new MushroomCrate(posX, posY));
						break;
					case ENTITY_TYPE_COIN:
						AddEntity(new Coin(posX, posY, false));
						break;
					case ENTITY_TYPE_PIPE_ENTRY:
						AddEntity(new PipeIn(posX, posY, true));
						break;
					case ENTITY_TYPE_GOOMBA:
						AddEntity(new Goomba(posX, posY - 1));
						break;
					case ENTITY_TYPE_KOOPA:
						AddEntity(new Koopa(posX, posY - 32));
						break;
					case ENTITY_TYPE_PIPE_OUT:
						
						AddEntity(new PipeOut(posX, posY));
						break;
					case ENTITY_TYPE_PIPE_IN_VERT:
						AddEntity(new PipeIn(posX, posY, false));
						break;
					case ENTITY_TYPE_FLAG:
						AddEntity(new Flag(posX - 16, posY));
						break;
					case ENTITY_TYPE_LEVEL_END:
						AddEntity(new LevelEnd(posX, posY));
						break;
					case ENTITY_TYPE_VINE:
						AddEntity(new VineBrick(posX, posY));
					default:
						break;
				}
			}
		}
	}
}

void GameScene::SwitchToSubLevel() {
	switchToSubLevelFlag = true;
}

void GameScene::SwitchToNextLevel() {
	switchToNextLevelFlag = true;
}

void GameScene::switchToNextLevel() {
	Time = 400;
	if(CurrentLevel->Name.compare("1") == 0) {
		Camera.x = 0;
		SwitchLevel("2", false, false);
	}
}

void GameScene::switchToSubLevel() {	
	if(CurrentLevel->Name.compare("1") == 0) {
		SwitchLevel("11", true, false);
	} else if(CurrentLevel->Name.compare("11") == 0) {
		SwitchLevel("1", false, true);
	}
}
