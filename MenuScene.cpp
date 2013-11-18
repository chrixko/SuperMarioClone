#include "Assets.h"
#include "Input.h"
#include "SceneManager.h"
#include "LevelSelectionScene.h"
#include "LoadScene.h"

#include "MenuScene.h"


MenuScene::MenuScene(void) : Scene() {
	IntroAnimation = Assets::Animations["menu"];
	
	Items[0] = new MenuItem((SCRWIDTH / 2) - 100, (SCRHEIGHT / 2) + 40, Assets::Graphics["menuitem_startgame"]);
	Items[0]->Selected = true;
	Items[1] = new MenuItem((SCRWIDTH / 2) - 100, (SCRHEIGHT / 2) + 75, Assets::Graphics["menuitem_leveleditor"]);
}


MenuScene::~MenuScene(void) {
}

void MenuScene::Init() {
	AddEntity(Items[0]);
	AddEntity(Items[1]);
}

void MenuScene::Update(float deltaTime) {
	Scene::Update(deltaTime);

	if(Input::IsKeyJustPressed(SDLK_UP)) {
		Items[0]->Selected = true;
		Items[1]->Selected = false;            
	}

	if(Input::IsKeyJustPressed(SDLK_DOWN)) {
		Items[0]->Selected = false;
		Items[1]->Selected = true; 
	}

	
	if(Items[0]->Clicked) {
		Player* p = new Player();
		Manager->SwitchScene(new LoadScene(p, "1"));	
	}
	if(Items[1]->Clicked) Manager->SwitchScene(new LevelSelectionScene());

	if(Input::IsKeyJustPressed(SDLK_ESCAPE)) {
		Manager->ExitGame = true;
	}		
}

void MenuScene::Draw(Surface* screen, float deltaTime) {
	IntroAnimation->Update(deltaTime);
	IntroAnimation->GetCurrentSurface()->CopyTo(screen, 0, 0);
	
	Scene::Draw(screen, deltaTime);
}
