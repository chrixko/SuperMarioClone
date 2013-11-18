#pragma once
#include "gravityentity.h"

class Fire : public GravityEntity {
	public:
		Fire(int posX, int posY, int direction);
		~Fire(void);

		float JumpSpeed;

		void Update(float deltaTime);
};

