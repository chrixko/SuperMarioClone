#pragma once
#include "entity.h"
class Coin : public Entity {
	public:
		Coin(int posX, int posY, bool jump);
		~Coin(void);

		Animation* JumpAnimation;
		Animation* StayAnimation;

		void Update(float deltaTime);

		bool Jump;
	private:
		float velocityY;
		vector3 originalPosition;

};