#include "GameScene.h"

#include "CameraEntity.h"


CameraEntity::CameraEntity(void) : Entity() {
	Type = "camera";
	Position.y = -100;
	SizeX = 200;
	SizeY = SCRHEIGHT + 100;	
}


CameraEntity::~CameraEntity(void) {
}

void CameraEntity::Init() {
	GScene = (GameScene*)Scene;
}

void CameraEntity::Update(float deltaTime) {	
	if(!CollidesWith("player")) {
		Scene->Camera.x = GScene->CurrentPlayer->Position.x - SizeX;		
		Position.x = Scene->Camera.x;
	}
}
