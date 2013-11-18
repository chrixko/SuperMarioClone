#include "Assets.h"
#include "Input.h"
#include "MenuItem.h"

MenuItem::MenuItem(int posX, int posY, Surface* graphic) : Entity() {
	Position.x = posX;
	Position.y = posY;

	Graphic = graphic;

	Selected = false;
	Clicked = false;
}

MenuItem::MenuItem(int posX, int posY, std::string text) {
	Position.x = posX;
	Position.y = posY;

	Text = text;

	Selected = false;
	Clicked = false;
}

MenuItem::~MenuItem(void) {
}

void MenuItem::Update(float deltaTime) {
	Clicked = Selected && Input::IsKeyJustPressed(SDLK_RETURN);	
}

void MenuItem::Draw(Surface* screen, float deltaTime) {
	if(Graphic == 0) {
		screen->Print(&Text[0], Position.x, Position.y + 5, 0xFFFFFF);
	} else {
		Entity::Draw(screen, deltaTime);
	}	

	if(Selected) {
		Assets::Graphics["menu_select"]->AlphaCopyTo(screen, Position.x - 30, Position.y);		
	}
}