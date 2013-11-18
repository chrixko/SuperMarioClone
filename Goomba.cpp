#include "Assets.h"
#include "Helper.h"
#include "GameScene.h"
#include "Goomba.h"
#include "ScoreEntity.h"

#define GOOMBA_SPEED 50

Goomba::Goomba(int posX, int posY) : GravityEntity() {
	WalkAnimation = new Animation(*Assets::Animations["goomba"]);
	CurrentAnimation = WalkAnimation;
	Graphic = Assets::Graphics["goomba"];

	Position.x = posX;
	Position.y = posY;

	direction = -1;
	Velocity.x = GOOMBA_SPEED * direction;

	SizeX = 32;
	SizeY = 32;

	Type = "enemy";	

	disappearTime = 1;
	disappearTimer = 0;
}


Goomba::~Goomba(void) {
}


void Goomba::Update(float deltaTime) {
	if(CurrentAnimation != 0) {
		GravityEntity::Update(deltaTime);

		if(CollidesWith("enemy") || CollidesWith("enemy_dead")) {
			OnHitSide();
		}

		SDL_Rect Top;
		Top.x = Position.x + 1;
		Top.y = Position.y;
		Top.w = SizeX - 1;
		Top.h = 3;

		if(GScene->CurrentPlayer->Velocity.y > 0 && Helper::SDL_IntersectRect(&Top, &GScene->CurrentPlayer->GetBottom())) {			
			GScene->CurrentPlayer->Velocity.y = -250;

			Position.y += 16;
			CurrentAnimation = 0;
			Graphic = Assets::Graphics["goomba"];
			Type = "enemy_dead";
			Scene->AddEntity(new ScoreEntity(Position.x, Position.y, 100));
		}

		if(CollidesWith("hit_brick") || CollidesWith("shell") || CollidesWith("fire")) {			
			CurrentAnimation = 0;
			Graphic = Assets::Graphics["goomba_flipped"];
			Type = "";
			Scene->AddEntity(new ScoreEntity(Position.x, Position.y, 200));
		}
	} else {
		if(strcmp(Type, "") != 0) {
			disappearTimer += deltaTime;
			if(disappearTimer >= disappearTime) {
				Scene->RemoveEntity(this);
			}
		} else {			
			if(CheckCollision) {
				Velocity.y = -300;
				CheckCollision = false;
			}

			GravityEntity::Update(deltaTime);
		}
	}
}

void Goomba::OnHitSide() {
	direction *= -1;
	Velocity.x = GOOMBA_SPEED * direction;
}