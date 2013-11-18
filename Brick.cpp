#include "Assets.h"
#include "Helper.h"
#include "GameScene.h"
#include "Brick.h"

#define BUMP_SPEED 100

Brick::Brick(int posX, int posY) {
	Graphic = Assets::Graphics["brick_normal"];

	Position.x = posX;
	Position.y = posY;

	originalPosition = Position;

	SizeX = SizeY = 32;

	Type = "brick";

	hit = false;

	Bottom.x = Position.x + 1 ;
	Bottom.y = Position.y + SizeY;
	Bottom.w = SizeX -1;
	Bottom.h = 4;	

	ZOrder = 10;

	Destroyable = true;
}

Brick::~Brick(void) {
}

void Brick::Init() {
	GScene = (GameScene*)Scene;
}

void Brick::Update(float deltaTime) {	
	if(!hit && GScene->CurrentPlayer->Velocity.y < 0 && Helper::SDL_IntersectRect(&Bottom, &GScene->CurrentPlayer->GetHitbox())) {
		OnHit();
		Type = "hit_brick";

		if(Destroyable && GScene->CurrentPlayer->Mode != PLAYER_MODE_SMALL) {
			GScene->CurrentPlayer->Velocity.y = 0;
			Scene->RemoveEntity(this);
		}
	}

	if(hit) {		
		Position.y -= BUMP_SPEED * deltaTime;

		if(Position.y < originalPosition.y - 10) {
			hit = false;
		}
	}

	if(!hit && Position.y < originalPosition.y) {
		Position.y += BUMP_SPEED * deltaTime;
		Position.y = min(Position.y, originalPosition.y);

		if(Position.y == originalPosition.y) {
			Type = "brick";
		}
	}
}

void Brick::OnHit() {
	hit = true;
}