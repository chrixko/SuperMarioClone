#pragma once

#include <vector>

#include "Level.h"

#include "scene.h"

class EditorScene :	public Scene {
	public:
		EditorScene(Level* level);
		~EditorScene(void);
		
		ENTITY_TYPE CurrentType;

		Level* CurrentLevel;

		void Init();
		void Update(float deltaTime);
		void Draw(Surface* screen, float deltaTime);

		void SetBlockValueFor(int tileIndex, bool value);
};

