#include "Assets.h"
#include "Helper.h"
#include "GameScene.h"
#include "ScoreEntity.h"

#include "Koopa.h"

#define KOOPA_SPEED 50
#define KOOPA_SHELL_SPEED 300

Koopa::Koopa(int posX, int posY) : GravityEntity() {
	WalkAnimations[KOOPA_DIRECTION_LEFT] = new Animation(*Assets::Animations["koopa_walk_left"]);
	WalkAnimations[KOOPA_DIRECTION_RIGHT] = new Animation(*Assets::Animations["koopa_walk_right"]);

	ShellAnimation = new Animation(*Assets::Animations["koopa_shell"]);
	DieAnimation = new Animation(*Assets::Animations["koopa_die"]);

	Direction = KOOPA_DIRECTION_LEFT;
	CurrentAnimation = WalkAnimations[Direction];

	Position.x = posX;
	Position.y = posY;

	Type = "enemy";

	SizeX = 32;
	SizeY = 48;

	Velocity.x = -KOOPA_SPEED;

	State = KOOPA_STATE_DEFAULT;
}

Koopa::~Koopa(void)
{
}

void Koopa::Update(float deltaTime) {	
	switch (State)
	{
		case KOOPA_STATE_DEFAULT:
			GravityEntity::Update(deltaTime);
			if(CollidesWith("enemy") || CollidesWith("enemy_dead")) {
				OnHitSide();
			}

			CurrentAnimation = WalkAnimations[Direction];

			SDL_Rect Top;
			Top.x = Position.x + 1;
			Top.y = Position.y;
			Top.w = SizeX - 1;
			Top.h = 3;

			if(GScene->CurrentPlayer->Velocity.y > 0 && Helper::SDL_IntersectRect(&Top, &GScene->CurrentPlayer->GetBottom())) {			
				GScene->CurrentPlayer->Velocity.y = -300;

				CurrentAnimation = ShellAnimation;		
				Type = "";
				State = KOOPA_STATE_JUMPED_ON;
				Scene->AddEntity(new ScoreEntity(Position.x, Position.y, 100));
			}

			if(CollidesWith("shell") || CollidesWith("fire")) {
				CurrentAnimation = DieAnimation;
				State = KOOPA_STATE_DYING;
				Scene->AddEntity(new ScoreEntity(Position.x, Position.y, 200));
			}

			break;
		case KOOPA_STATE_JUMPED_ON:
			if(CurrentAnimation->Finished) {
				Position.y += 20;
				SizeY = 28;				

				State = KOOPA_STATE_SHELL;

				Velocity.x = 0;
			}
			break;
		case KOOPA_STATE_DYING:			
			if(CheckCollision) {
				Velocity.y = -300;
				CheckCollision = false;
			}

			GravityEntity::Update(deltaTime);
			break;
		case KOOPA_STATE_SHELL:
			GravityEntity::Update(deltaTime);
			CurrentAnimation = 0;
			Graphic = ShellAnimation->Sprites[1];

			if(Velocity.x == 0) {
				SDL_Rect Top;
				Top.x = Position.x + 1;
				Top.y = Position.y;
				Top.w = SizeX - 1;
				Top.h = 3;

				if(GScene->CurrentPlayer->Velocity.y > 0 && Helper::SDL_IntersectRect(&Top, &GScene->CurrentPlayer->GetBottom())) {	
					GScene->CurrentPlayer->Velocity.y = -50;
					Type = "shell";

					if(GScene->CurrentPlayer->Position.x <= Top.x) {
						Velocity.x = KOOPA_SHELL_SPEED;
					} else {
						Velocity.x = -KOOPA_SHELL_SPEED;
					}					
				}
			}


			break;
		default:
			break;
	}

}

void Koopa::OnHitSide() {
	Velocity.x *= -1;

	if(Velocity.x < 0) {
		Direction = KOOPA_DIRECTION_LEFT;
	} else {
		Direction = KOOPA_DIRECTION_RIGHT;
	}	
}
