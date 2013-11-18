#pragma once
#include "Player.h"

#include "scene.h"

class LoadScene : public Scene {
	public:
		LoadScene(Player* player, std::string level);
		~LoadScene(void);
		
		std::string Level;
		Player* CurrentPlayer;

		void Update(float deltaTime);
		void Draw(Surface* screen, float deltaTime);

	private:
		float stayTimer;


};

