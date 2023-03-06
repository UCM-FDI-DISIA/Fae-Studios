#include "Image.h"
#include "../ecs/Entity.h"
void Image::render() {
	texture->render(getRect(), transform->getRotation());
}

SDL_Rect Image::getRect() const{
	SDL_Rect destRect;

	destRect.x = transform->getPosition().getX(); destRect.y = transform->getPosition().getY();
	destRect.w = transform->getWidth(); destRect.h = transform->getHeight();
	
	return destRect;
}

void Image::initComponent() {
	transform = ent_->getComponent<Transform>();
}
