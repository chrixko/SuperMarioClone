#include "Assets.h"
#include "Mushroom.h"

#define MUSHROOM_SPEED 100
#define MUSHROOM_APPEAR_SPEED 50

Mushroom::Mushroom(int posX, int posY, MUSHROOM_TYPE type) : GravityEntity() {
	Position.x = posX;
	Position.y = posY;

	MushroomType = type;

	originalPosition = Position;

	if(type == MUSHROOM_TYPE_NORMAL) {
		Graphic = Assets::Graphics["mushroom"];
		Velocity.x = MUSHROOM_SPEED;
	} else {
		CurrentAnimation = Assets::Animations["flower"];
	}
	
	SizeX = SizeY = 32;	
	
	Velocity.y = -MUSHROOM_APPEAR_SPEED;
	direction = 1;

	slide = false;
}

Mushroom::~Mushroom(void) {
}

void Mushroom::Update(float deltaTime) {	
	if(slide) {
		GravityEntity::Update(deltaTime);
		if(CollidesWith("hit_brick")) {
			Velocity.y -= 300;
		}

		if(CollidesWithTiles(Position.x + Velocity.x * deltaTime, Position.y - 1)) {
			direction *= -1;
			Velocity.x= MUSHROOM_SPEED * direction;
		}
	} else {
		if(Position.y > originalPosition.y - 32) {
			Position.y += Velocity.y * deltaTime;
		} else {
			Velocity.y = 0;
			Type = "mushroom";
			if(MushroomType == MUSHROOM_TYPE_NORMAL) {
				slide = true;
			}			
		}
	}	
}

void Mushroom::FixedUpdate(float deltaTime) {
	if(slide) {
		GravityEntity::FixedUpdate(deltaTime);
	}
}