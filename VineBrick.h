#pragma once
#include "brick.h"
class VineBrick : public Brick {
	public:
		VineBrick(int posX, int posY);
		~VineBrick(void);

		bool Growing;
		float VineY;

		void Update(float deltaTime);
		void OnHit();

		void Draw(Surface* screen, float deltaTime);
};