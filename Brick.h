#pragma once

#include "Entity.h"

class GameScene;

class Brick : public Entity {
	public:
		Brick(int posX, int posY);
		~Brick(void);

		GameScene* GScene;
		SDL_Rect Bottom;

		bool Destroyable;

		void Init();
		void Update(float deltaTime);		
			

		virtual void OnHit();
	private:
		bool hit;
		vector3 originalPosition;
};

