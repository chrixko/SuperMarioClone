#include "Assets.h"
#include "Coin.h"
#include "Scene.h"

#include "CoinBrick.h"


CoinBrick::CoinBrick(int posX, int posY) : Brick(posX, posY) {	
	CoinCount = 5;
	Destroyable = false;
}


CoinBrick::~CoinBrick(void)
{
}

void CoinBrick::OnHit() {
	if(CoinCount > 0) {
		Brick::OnHit();

		CoinCount--;
		Scene->AddEntity(new Coin(Position.x + 8, Position.y - 28, true));

		if(CoinCount == 0) {
			Graphic = Assets::Graphics["empty_crate"];
		}
	}	
}
