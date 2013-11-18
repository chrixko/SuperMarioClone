#pragma once
#include <string>
#include "template.h"
#include "Assets.h"
#include "SDL.h"

class Helper {
	public:
		static int GetRandomInt(int min, int max);
		static bool SDL_IntersectRect(const SDL_Rect *A, const SDL_Rect *B, SDL_Rect *intersection);
		static bool SDL_IntersectRect(const SDL_Rect *A, const SDL_Rect *B);

		static float DegreesToRadians(float degrees) { return degrees * (PI / 180); }

		static int Sign(float value) { return (value > 0) ? 1 : ((value < 0) ? -1 : 0) ; }
		static std::string FixedLength(int value, int digits = 3);

		static void PrintText(int posX, int posY, std::string text, Surface* screen) {
			for(int i = 0; i < text.length(); i++) {
				std::string charKey = "chars_";
				charKey += text[i];
				Assets::Graphics[charKey]->AlphaCopyTo(screen, posX + (i*16), posY);
			}
		}
};