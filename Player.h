#pragma once

#include <map>
#include "GravityEntity.h"

enum PLAYER_DIRECTION {
	SMALL_PLAYER_DIRECTION_LEFT,
	SMALL_PLAYER_DIRECTION_RIGHT,
	BIG_PLAYER_DIRECTION_LEFT,
	BIG_PLAYER_DIRECTION_RIGHT,
	FIRE_PLAYER_DIRECTION_LEFT,
	FIRE_PLAYER_DIRECTION_RIGHT
};

enum PLAYER_MODE {
	PLAYER_MODE_SMALL,
	PLAYER_MODE_BIG,
	PLAYER_MODE_FIRE
};

enum PLAYER_STATE {
	PLAYER_STATE_DEFAULT,
	PLAYER_STATE_GROWING,
	PLAYER_STATE_SHRINKING,
	PLAYER_STATE_DYING,
	PLAYER_STATE_PIPE_IN,
	PLAYER_STATE_ON_FLAG,
	PLAYER_STATE_GO_TO_FINISH,
	PLAYER_STATE_ON_VINE
};

class GameScene;

class Player : public GravityEntity {
	public:
		Player(void);
		~Player(void);

		std::map<PLAYER_DIRECTION, Animation*> RunAnimations;
		std::map<PLAYER_DIRECTION, Surface*> IdleGraphics;
		std::map<PLAYER_DIRECTION, Surface*> JumpGraphics;
		std::map<PLAYER_DIRECTION, Surface*> TurnGraphics;
		std::map<PLAYER_DIRECTION, Animation*> GrowAnimations;
		std::map<PLAYER_DIRECTION, Animation*> ShrinkAnimations;


		float HorizontalAcceleration;

		PLAYER_MODE Mode;
		PLAYER_DIRECTION Direction;
		PLAYER_STATE State;

		int Score;
		int Lifes;
		int CoinCount;

		float DefaultGravity;
		float ActualGravity;
		float MinimunGravity;

		float MaxSpeed;

		void Init();
		void Update(float deltaTime);
		void Draw(Surface* screen, float deltaTime);
		
		SDL_Rect GetBottom();

		void Die();
	private:		
		void animate();
		void updateDefaultState(float deltaTime);
		
		bool hurtable;
		float notHurtableTime;
		float notHurtableTimer;

		float dieTimer;

		float pipeTime;
		float pipeTimer;
};