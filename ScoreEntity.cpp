#include "Scene.h"
#include "GameScene.h"
#include "Player.h"
#include "ScoreEntity.h"


ScoreEntity::ScoreEntity(int posX, int posY, int score) {
	Position.x = posX;
	Position.y = posY;

	Value = score;
	stayTimer = 0;
}

ScoreEntity::~ScoreEntity(void)
{
}

void ScoreEntity::Update(float deltaTime) {
	Position.x += 50 * deltaTime;
	Position.y -= 50 * deltaTime;

	stayTimer += deltaTime;
	if(stayTimer > 1.0f) {
		Scene->RemoveEntity(this);
		((GameScene*)Scene)->CurrentPlayer->Score += Value;
	}
}

void ScoreEntity::Draw(Surface* screen, float deltaTime) {
	screen->Print(&std::to_string(Value)[0], Position.x - Scene->Camera.x, Position.y - Scene->Camera.y, 0xFFFFFF);
}