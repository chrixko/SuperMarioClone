#include "Assets.h"
#include "Scene.h"
#include "GameScene.h"
#include "Player.h"
#include "ScoreEntity.h"

#include "Coin.h"

#define COIN_JUMP_SPEED 500

Coin::Coin(int posX, int posY, bool jump) : Entity() {
	Position.x = posX;
	Position.y = posY;

	JumpAnimation = new Animation(*Assets::Animations["coin_jump"]);
	StayAnimation = new Animation(*Assets::Animations["coin_stay"]);

	Jump = jump;

	if(jump) {
		CurrentAnimation = JumpAnimation;
		velocityY = -COIN_JUMP_SPEED;
	} else {
		Type = "coin";
		SizeX = 20;
		SizeY = 28;
		CurrentAnimation = StayAnimation;
	}

	originalPosition = Position;
}


Coin::~Coin(void) {
	CurrentAnimation = 0;
	delete JumpAnimation;	
}

void Coin::Update(float deltaTime) {
	if(Jump) {
		if(Position.y < originalPosition.y - 75) {
			velocityY *= -1;
		}

		if(velocityY > 0 && Position.y >= originalPosition.y) {
			Scene->RemoveEntity(this);
			((GameScene*)Scene)->CurrentPlayer->CoinCount++;
			Scene->AddEntity(new ScoreEntity(Position.x, Position.y, 200));
		}

		Position.y += velocityY * deltaTime;
	} else {
		if(CollidesWith("player")) {
			Scene->RemoveEntity(this);
			((GameScene*)Scene)->CurrentPlayer->CoinCount++;
			Scene->AddEntity(new ScoreEntity(Position.x, Position.y, 200));
		}
	}
}
