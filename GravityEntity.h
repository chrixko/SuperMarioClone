#pragma once
#include "Scene.h"
#include "entity.h"

class GameScene;

class GravityEntity : public Entity {
	public:
		GravityEntity(void);
		~GravityEntity(void);
		
		GameScene* GScene;
		vector3 Velocity;
		
		float Gravity;
		bool CheckCollision;
		

		void Init();
		virtual void Update(float deltaTime);
		void FixedUpdate(float deltaTime);
		SDL_Rect* CollidesWithTiles(int nextX, int nextY);
		
		virtual void OnHitSide();

		bool OnGround;

		virtual void Die() {
			Scene->RemoveEntity(this);
		}
};