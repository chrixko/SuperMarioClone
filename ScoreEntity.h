#pragma once
#include "entity.h"
class ScoreEntity : public Entity {
	public:
		ScoreEntity(int posX, int posY, int score);
		~ScoreEntity(void);

		int Value;
		float stayTimer;

		void Update(float deltaTime);
		void Draw(Surface* screen, float deltaTime);
};

