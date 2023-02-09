#include "CollisionObject.h"

CollisionObject::CollisionObject(Vector2D pos, Texture* texture, Scale scale) : GameObject(pos, texture, scale) {

}

CollisionObject::~CollisionObject() {

}

bool CollisionObject::collide(const SDL_Rect& obj, SDL_Rect& result) {
	const SDL_Rect rect = getRect();

	return SDL_IntersectRect(&obj, &rect, &result);
}
