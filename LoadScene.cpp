#include "Helper.h"
#include "SceneManager.h"
#include "GameScene.h"
#include "LoadScene.h"


LoadScene::LoadScene(Player* player, std::string level) {
	Level = level;
	CurrentPlayer = player;
	CurrentPlayer->Position.x = (SCRWIDTH / 2) - 50;
	CurrentPlayer->Position.y = (SCRHEIGHT / 2) - 32;
	stayTimer = 0;
}


LoadScene::~LoadScene(void)
{
}

void LoadScene::Update(float deltaTime) {
	stayTimer += deltaTime;

	if(stayTimer >= 2.0f) {
		Manager->SwitchScene(new GameScene(CurrentPlayer, Level));
	}
}

void LoadScene::Draw(Surface* screen, float deltaTime) {
	//CurrentPlayer->Scene = this;
	CurrentPlayer->Draw(screen, deltaTime);
	std::string lives = "x";
	lives += std::to_string(CurrentPlayer->Lifes);
	Helper::PrintText(CurrentPlayer->Position.x + 32, CurrentPlayer->Position.y + 16, lives, screen);
}
