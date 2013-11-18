#pragma once

#include "Level.h"
#include "Player.h"
#include "CameraEntity.h"

#include "scene.h"

class GameScene : public Scene {
public:
	GameScene(void);
	GameScene(Player* player, std::string level);
	~GameScene(void);

	Player* CurrentPlayer;
	CameraEntity* CurrentCamera;
	Level* CurrentLevel;
	float Time;

	void Init();
	void Update(float deltaTime);
	void FixedUpdate(float deltaTime);
	void Draw(Surface* screen, float deltaTime);

	void SwitchToSubLevel();
	void SwitchToNextLevel();

	void InitCurrentLevel();	
	void SwitchLevel(std::string name, bool isSubLevel, bool placePlayerAtTubeOut);
private:
	bool switchToSubLevelFlag;
	bool switchToNextLevelFlag;
	void switchToSubLevel();
	void switchToNextLevel();
};

