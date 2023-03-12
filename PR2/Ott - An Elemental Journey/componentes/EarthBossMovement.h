#pragma once
#include "Component.h"
#include "Transform.h"
  
//brainstorm literal porque no se como hacerlo jeje
class EarthBossMovement : public Component
{
	enum Position {pos1, pos2, pos3, pos4, pos5};
private:
	Transform* tr_;
	Position pos;
	SDL_Rect trigger;
};

