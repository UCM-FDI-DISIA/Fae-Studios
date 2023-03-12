#include "ColliderVine.h"
void ColliderVine::update() {
	if (my_rect.y > posFinalC.getY()) {
	    setPos(Vector2D(my_rect.x, my_rect.y - 2));
	}
}