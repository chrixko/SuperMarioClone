#include "Assets.h"
#include "Scene.h"
#include "Mushroom.h"
#include "GameScene.h"

#include "MushroomCrate.h"

MushroomCrate::MushroomCrate(int posX, int posY) : CoinCrate(posX, posY) {
	Destroyable = false;
}


MushroomCrate::~MushroomCrate(void) {
}

void MushroomCrate::OnHit() {
	if(CurrentAnimation != 0) {
		Brick::OnHit();
		
		MUSHROOM_TYPE type = GScene->CurrentPlayer->Mode == PLAYER_MODE_SMALL ? MUSHROOM_TYPE_NORMAL : MUSHROOM_TYPE_FIRE;

		Scene->AddEntity(new Mushroom(Position.x, Position.y, type));
	}

	CurrentAnimation = 0;
	Graphic = Assets::Graphics["empty_crate"];
}