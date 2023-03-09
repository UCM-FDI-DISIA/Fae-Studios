#pragma once
#include "Component.h"
#include "../dependencies/Vector2D.h"
#include "../Src/Entity.h"
class ColliderVine : public Component
{
private:
	SDL_Rect my_rect;

public:
	constexpr static cmpId_type id = ecs::_COLLIDERVINE;
	ColliderVine(SDL_Rect d):my_rect(d) {};
	virtual ~ColliderVine() {};
	SDL_Rect getRect() { return my_rect; }
	inline Vector2D getPos() { return Vector2D(my_rect.x, my_rect.y); }
	inline void setPos(Vector2D newPos) { my_rect.x = newPos.getX(); my_rect.y = newPos.getY();
	}

};

