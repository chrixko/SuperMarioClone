#pragma once

#include "CoinCrate.h"

class MushroomCrate : public CoinCrate {
	public:
		MushroomCrate(int posX, int posY);
		~MushroomCrate(void);

		void OnHit();
};

