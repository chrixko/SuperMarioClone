#include "Assets.h"
#include "PipeIn.h"


PipeIn::PipeIn(int posX, int posY, bool horizontal) : Entity() {	
	Graphic = horizontal ? Assets::Graphics["pipe_horizontal"] : Assets::Graphics["pipe_vertical"];

	Position.x = posX;
	Position.y = posY;
	
	SizeX = 32;
	SizeY = horizontal ? 32 : 64;

	if(horizontal) {
		Offset.x = 16;
	}

	Type = horizontal ? "pipe_in" : "pipe_in_vert";
	ZOrder = 30;

	DrawHitbox = false;
}


PipeIn::~PipeIn(void) {
}
