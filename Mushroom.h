#pragma once

#include "GravityEntity.h"

enum MUSHROOM_TYPE {
	MUSHROOM_TYPE_NORMAL,
	MUSHROOM_TYPE_FIRE
};

class Mushroom : public GravityEntity {
	public:
		Mushroom(int posX, int posY, MUSHROOM_TYPE type);
		~Mushroom(void);

		MUSHROOM_TYPE MushroomType;

		void Update(float deltaTime);
		void FixedUpdate(float deltaTime);
	private:
		vector3 originalPosition;
		bool slide;
		int direction;

};

