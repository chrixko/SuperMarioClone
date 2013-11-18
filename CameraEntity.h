#pragma once

#include "entity.h"

class GameScene;

class CameraEntity : public Entity {
	public:
		CameraEntity(void);
		~CameraEntity(void);

		void Init();
		void Update(float deltaTime);

		GameScene* GScene;
};

