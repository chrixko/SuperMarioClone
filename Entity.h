#pragma once

#include <string>
#include <vector>

#include "SDL.h"
#include "template.h"
#include "surface.h"
#include "Animation.h"

class Scene;	

class Entity {
	public:
		Entity(void);
		~Entity(void);

		Surface* Graphic;
		Animation* CurrentAnimation;

		Scene* Scene;
		vector3 Position;

		int SizeX;
		int SizeY;
		
		vector3 Offset;
		vector3 DrawOffset;

		bool Hidden;
		int ZOrder;

		char* Type;			
		Entity* CollidesWith(char* type);
		Entity* CollidesWith(char* type, int nextX, int nextY);
		bool CollidesWithTiles(vector3 velocity);
		//bool CollidesWithTiles(int nextX, int nextY);
		bool DrawHitbox;

		//Init -> Entity gets added to the game
		bool Inited;
		virtual void Init() { Inited = true; };
		virtual void Update(float deltaTime) {};
		virtual void FixedUpdate(float deltaTime) {};
		virtual void Draw(Surface* screen, float deltaTime);
		//Destroy -> Entity gets removed from the game
		virtual void Destroy() {};

		virtual SDL_Rect GetHitbox();

		static bool CompareByZOrder(const Entity* a, const Entity* b);
};