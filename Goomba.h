#pragma once
#include "gravityentity.h"
class Goomba :	public GravityEntity {
	public:
		Goomba(int posX, int posY);
		~Goomba(void);

		Animation* WalkAnimation;

		void Update(float deltaTime);

		void OnHitSide();
	private:
		int direction;
		float disappearTime;
		float disappearTimer;
};