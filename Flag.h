#pragma once
#include "GravityEntity.h"

class GameScene;

class Flag : public GravityEntity {
	public:
		Flag(int posX, int posY);
		~Flag(void);

		void Update(float deltaTime);
	private:
		bool startFalling;

};