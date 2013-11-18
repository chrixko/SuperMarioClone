#pragma once
#include "gravityentity.h"

enum KOOPA_DIRECTION {
	KOOPA_DIRECTION_LEFT,
	KOOPA_DIRECTION_RIGHT
};

enum KOOPA_STATE {
	KOOPA_STATE_DEFAULT,
	KOOPA_STATE_JUMPED_ON,
	KOOPA_STATE_DYING,
	KOOPA_STATE_SHELL
};

class Koopa : public GravityEntity {
	public:
		Koopa(int posX, int posY);
		~Koopa(void);

		std::map<KOOPA_DIRECTION, Animation*> WalkAnimations;
		Animation* ShellAnimation;
		Animation* DieAnimation;

		KOOPA_DIRECTION Direction;
		KOOPA_STATE State;

		bool IsShell;

		void Update(float deltaTime);

		void OnHitSide();
	private:
		int direction;
};

