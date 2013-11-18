#include "Assets.h"
#include "Scene.h"
#include "Helper.h"
#include "GameScene.h"
#include "Input.h"


#include "VineBrick.h"


VineBrick::VineBrick(int posX, int posY) : Brick(posX, posY) {
	Growing = false;
	VineY = posY;
	Destroyable = false;
}


VineBrick::~VineBrick(void)
{
}

void VineBrick::Update(float deltaTime) {
	Brick::Update(deltaTime);

	if(Growing) {
		VineY -= 75 * deltaTime;
	}

	if(VineY < -32) {
		Growing = false;
	}

	SDL_Rect r;
	r.x = Position.x;
	r.y = VineY;
	r.w = 32;
	r.h = Position.y - VineY;

	if(Helper::SDL_IntersectRect(&r, &GScene->CurrentPlayer->GetHitbox())) {
		if(Input::IsKeyJustPressed(SDLK_UP)) {			
			GScene->CurrentPlayer->State = PLAYER_STATE_ON_VINE;
			GScene->CurrentPlayer->Velocity.y = 0;
		}
	} else {
		if(GScene->CurrentPlayer->State == PLAYER_STATE_ON_VINE) {
			GScene->CurrentPlayer->State = PLAYER_STATE_DEFAULT;
		}
	}
}

void VineBrick::OnHit() {
	if(VineY == Position.y) {
		Brick::OnHit();
		Growing = true;
	}

	CurrentAnimation = 0;
	Graphic = Assets::Graphics["empty_crate"];
}

void VineBrick::Draw(Surface* screen, float deltaTime) {
	Assets::Graphics["vine_top"]->AlphaCopyTo(screen, Position.x - Scene->Camera.x, VineY);
	int vineCounts = floor((Position.y - VineY) / 32);
	for(int i = 0; i < vineCounts; i++) {
		Assets::Graphics["vine_part"]->AlphaCopyTo(screen, Position.x - Scene->Camera.x, VineY + 32 + (i * 32));
	}

	Brick::Draw(screen, deltaTime);
	if(VineY == Position.y) {
		Assets::Graphics["vine_top"]->AlphaCopyTo(screen, Position.x - Scene->Camera.x, Position.y);
	}	
}
