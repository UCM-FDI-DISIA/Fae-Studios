//LIMPIO

#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include "../ecs/Entity.h"
#include <SDL.h>

class ColliderVine : public Component {
private:
	SDL_Rect my_rect;

public:
	constexpr static ecs::cmpId_type id = ecs::_COLLIDERVINE;
	
	ColliderVine(SDL_Rect d): my_rect(d) {};
	
	inline SDL_Rect getRect() { return my_rect; }
	inline Vector2D getPos() { return Vector2D(my_rect.x, my_rect.y); }
	inline void setPos(Vector2D newPos) { my_rect.x = newPos.getX(); my_rect.y = newPos.getY(); }

};
