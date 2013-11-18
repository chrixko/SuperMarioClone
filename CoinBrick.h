#pragma once

#include "brick.h"

class CoinBrick : public Brick {
	public:
		CoinBrick(int posX, int posY);
		~CoinBrick(void);

		int CoinCount;

		void OnHit();
};

