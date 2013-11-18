#include "Assets.h"
#include "Scene.h"

#include "Coin.h"
#include "CoinCrate.h"

CoinCrate::CoinCrate(int posX, int posY) : Brick(posX, posY) {
	DefaultAnimation = new Animation(*Assets::Animations["coincrate"]);
	CurrentAnimation = DefaultAnimation;
	Destroyable = false;
}

CoinCrate::~CoinCrate(void) {
}

void CoinCrate::OnHit() {
	if(CurrentAnimation != 0) {
		Brick::OnHit();
		Scene->AddEntity(new Coin(Position.x + 8, Position.y - 28, true));
	}

	CurrentAnimation = 0;
	Graphic = Assets::Graphics["empty_crate"];
}