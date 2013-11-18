#include <stdlib.h>
#include "Helper.h"

int Helper::GetRandomInt(int min, int max) {
	return (rand()%(max-min))+min;
}

//Copied from original source since I could not find it in the included SDL header
bool Helper::SDL_IntersectRect(const SDL_Rect *A, const SDL_Rect *B, SDL_Rect *intersection)
{
	int Amin, Amax, Bmin, Bmax;

	/* Horizontal intersection */
	Amin = A->x;
	Amax = Amin + A->w;
	Bmin = B->x;
	Bmax = Bmin + B->w;
	if(Bmin > Amin)
			Amin = Bmin;
	intersection->x = Amin;
	if(Bmax < Amax)
			Amax = Bmax;
	intersection->w = Amax - Amin > 0 ? Amax - Amin : 0;

	/* Vertical intersection */
	Amin = A->y;
	Amax = Amin + A->h;
	Bmin = B->y;
	Bmax = Bmin + B->h;
	if(Bmin > Amin)
			Amin = Bmin;
	intersection->y = Amin;
	if(Bmax < Amax)
			Amax = Bmax;
	intersection->h = Amax - Amin > 0 ? Amax - Amin : 0;

	return (intersection->w && intersection->h);
}

bool Helper::SDL_IntersectRect(const SDL_Rect *A, const SDL_Rect *B) {
	SDL_Rect inter;
	return SDL_IntersectRect(A, B, &inter);
}

std::string Helper::FixedLength(int value, int digits) {
	unsigned int uvalue = value;
	if (value < 0) {
		uvalue = -uvalue;
	}
	std::string result;
	while (digits-- > 0) {
		result += ('0' + uvalue % 10);
		uvalue /= 10;
	}
	if (value < 0) {
		result += '-';
	}
	std::reverse(result.begin(), result.end());
	return result;
}