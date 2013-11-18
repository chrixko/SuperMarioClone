#include "Helper.h"
#include "GameScene.h"

#include "GravityEntity.h"


GravityEntity::GravityEntity(void) : Entity() {
	OnGround = false;
	Gravity = 24.0f;
	CheckCollision = true;
	GScene = 0;
}

GravityEntity::~GravityEntity(void) {
}

void GravityEntity::Init() {
	Entity::Init();
	GScene = (GameScene*)Scene;
}

void GravityEntity::Update(float deltaTime) {
	if(CheckCollision) {
		if(CollidesWithTiles(Position.x, Position.y + 1)) {
			OnGround = true;
		} else {
			OnGround = false;
		}

		if(OnGround && Velocity.y > 0) {
			Velocity.y = 0;
		}

		vector3 vel = Velocity * deltaTime;
	
		if(Velocity.y != 0) {
			SDL_Rect* tileBox = CollidesWithTiles(Position.x, Position.y + vel.y);
			if(!tileBox) {
				Position.y += vel.y;
			} else {
				Velocity.y = 0;
				if(vel.y > 0) {
					Position.y = tileBox->y - SizeY - 1;
				}
			}
		}

		if(Velocity.x != 0) {
			if(!CollidesWithTiles(Position.x + vel.x, Position.y - 1)) {
				Position.x += vel.x;
			} else {
				OnHitSide();
			}
		}
	} else {
		OnGround = false;
		Position += Velocity * deltaTime;
	}
}

void GravityEntity::OnHitSide() {
	Velocity.x = 0;
}

void GravityEntity::FixedUpdate(float deltaTime) {
	if(!OnGround) {
		Velocity.y += Gravity;
	}	
}

SDL_Rect* GravityEntity::CollidesWithTiles(int nextX, int nextY) {
	SDL_Rect box = GetHitbox();
	
	box.x = nextX + Offset.x;
	box.y = nextY + Offset.y;	

	Tile* tile = GScene->CurrentLevel->GetTile(box.x, box.y);
	if(tile != 0 && tile->Blocks) {
		return &tile->GetHitbox();
	}

	tile = GScene->CurrentLevel->GetTile(box.x + box.w, box.y);
	if(tile != 0 && tile->Blocks) {
		return &tile->GetHitbox();
	}

	tile = GScene->CurrentLevel->GetTile(box.x, box.y + box.h);
	if(tile != 0 && tile->Blocks) {
		return &tile->GetHitbox();
	}

	tile = GScene->CurrentLevel->GetTile(box.x + box.w, box.y + box.h);
	if(tile != 0 && tile->Blocks) {
		return &tile->GetHitbox();
	}

	Entity* brick = CollidesWith("brick", nextX, nextY);	
	if(brick) {
		return &brick->GetHitbox();
	}

	brick = CollidesWith("hit_brick", nextX, nextY);	
	if(brick) {
		return &brick->GetHitbox();
	}

	return 0;  
}