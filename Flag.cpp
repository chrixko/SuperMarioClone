#include "Assets.h"
#include "GameScene.h"
#include "Flag.h"


Flag::Flag(int posX, int posY) : GravityEntity() {
	Position.x = posX;
	Position.y = posY;

	CheckCollision = false;
	OnGround = true;

	SizeX = SizeY = 32;

	Type = "flag";
	startFalling = false;
	Graphic = Assets::Graphics["flag"];

	DrawHitbox = false;
}

Flag::~Flag(void) {
}

void Flag::Update(float deltaTime) {
	
	if(!startFalling && GScene->CurrentPlayer->State == PLAYER_STATE_DEFAULT && GScene->CurrentPlayer->Position.x + 32 >= Position.x + 32) {
		GScene->CurrentPlayer->State = PLAYER_STATE_ON_FLAG;
		GScene->CurrentPlayer->Position.x = Position.x;
		GScene->CurrentPlayer->Velocity.x = 0;
		GScene->CurrentPlayer->Velocity.y = 200;

		startFalling = true;
	}

	if(startFalling) {
		if(GScene->Time > 0) {
			GScene->Time--;
			GScene->CurrentPlayer->Score += 50;
		}

		if(!CollidesWithTiles(Position.x, Position.y)) {
			Position.y += 200 * deltaTime;
		} else {
			if(GScene->Time <= 0) {
				GScene->Time = 0;
				GScene->CurrentPlayer->Velocity.x = 200;
				GScene->CurrentPlayer->State = PLAYER_STATE_GO_TO_FINISH;
			}
		}
	}
}
