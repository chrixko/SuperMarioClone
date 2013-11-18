#include <algorithm>
#include "template.h"

#include "Helper.h"
#include "SceneManager.h"

#include "Scene.h"

Scene::Scene(void) {
	Manager = 0;
}

Scene::~Scene(void) {
}

void Scene::AddEntity(Entity* entity) {
	entity->Scene = this;
	if(!entity->Inited) {
		entity->Init();
	}	

	Entities.push_back(entity);

	sort(Entities.begin(), Entities.end(), Entity::CompareByZOrder);
}

void Scene::RemoveEntity(Entity* entity) {
	if(entity != 0) {
		entity->Destroy();
		Entities.erase(std::remove(Entities.begin(), Entities.end(), entity), Entities.end());
		ToDeleteEntities.push_back(entity);
	}
}

void Scene::RemoveEntityWithoutDestroy(Entity* entity) {
	Entities.erase(std::remove(Entities.begin(), Entities.end(), entity), Entities.end());
}

Entity* Scene::Colliding(Entity* entA, char* type) {
	return Colliding(entA, type, entA->Position.x, entA->Position.y);
}

Entity* Scene::Colliding(Entity* entA, char* type, int nextX, int nextY) {
	if(strlen(entA->Type) != 0) {
		SDL_Rect hA;
		hA = entA->GetHitbox();
		hA.x = nextX + entA->Offset.x;
		hA.y = nextY + entA->Offset.y;

		for(unsigned int i = 0; i < Entities.size(); i++) {
			Entity* ent = Entities[i];

			if(entA != ent && strcmp(ent->Type, type) == 0 && Colliding(&hA, &ent->GetHitbox())) {
				return ent;
			}
		}
	}

	return 0;
}

bool Scene::Colliding(SDL_Rect* hA, SDL_Rect* hB) {	
	return Helper::SDL_IntersectRect(hA, hB);
}

bool Scene::Colliding(Entity* entA, Entity* entB) {
	return Colliding(&entA->GetHitbox(), &entB->GetHitbox());
}

void Scene::Update(float deltaTime) {
	if(Entities.size() > 0) {
		for(int i = Entities.size() -1; i >= 0; i--) {
			if(Entities[i] != 0) {
				Entities[i]->Update(deltaTime);
			}			
		}
	}
}

void Scene::FixedUpdate(float deltaTime) {
	if(Entities.size() > 0) {
		for(int i = Entities.size() -1; i >= 0; i--) {
			if(Entities[i] != 0) {
				Entities[i]->FixedUpdate(deltaTime);
			}			
		}
	}

	freeEntities();
}

void Scene::Draw(Surface* screen, float deltaTime) {
	for(unsigned int i = 0; i < Entities.size(); i++) {
		if(Entities[i] != 0) {
			Entities[i]->Draw(screen, deltaTime);
		}		
	}
}

void Scene::freeEntities() {
	int size = ToDeleteEntities.size();
	if(size > 0) {
		for(int i = size -1; i >= 0; i--) {
			Entity* ent = ToDeleteEntities[i];
												   
			ToDeleteEntities.erase(ToDeleteEntities.begin() + i);            

			delete ent;            
		}        
	}
}

void Scene::Destroy() {
	for(unsigned int i = 0; i < Entities.size(); i++) {
		if(Entities[i] != 0) {
			Entities[i]->Destroy();
		}		
	}
}

