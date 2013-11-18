#include "Assets.h"
#include "Scene.h"
#include "Fire.h"

#define FIRE_SPEED 400

Fire::Fire(int posX, int posY, int direction) : GravityEntity() {
	CurrentAnimation = new Animation(*Assets::Animations["fire"]);

	Position.x = posX;
	Position.y = posY;

	SizeX = SizeY = 16;
	Type = "fire";

	JumpSpeed = -300;

	Velocity.x = direction * FIRE_SPEED;
}


Fire::~Fire(void)
{
}

void Fire::Update(float deltaTime) {
	GravityEntity::Update(deltaTime);

	if(OnGround) {
		Velocity.y = JumpSpeed;
		JumpSpeed += 50;

		if(JumpSpeed > -100) {
			Scene->RemoveEntity(this);
		}
	}
}
