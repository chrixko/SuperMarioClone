#pragma once

#include "brick.h"

class CoinCrate : public Brick {
	public:
		CoinCrate(int posX, int posY);
		~CoinCrate(void);

		Animation* DefaultAnimation;

		void OnHit();
};