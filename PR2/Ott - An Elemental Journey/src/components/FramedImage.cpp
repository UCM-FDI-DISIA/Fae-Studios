#include "../utils/checkML.h"
#include "FramedImage.h"
#include "../sdlutils/Texture.h"
#include "../ecs/Entity.h"


SDL_Rect FramedImage::getRect() const
{
    SDL_Rect destRect;

    destRect.x = transform->getPosition().getX(); destRect.y = transform->getPosition().getY();
    destRect.w = transform->getWidth(); destRect.h = transform->getHeight();

    return destRect;
}

void FramedImage::render() {
    texture->render({ currentCol * getFrameWidth(), currentRow * getFrameHeight(), getFrameWidth(), getFrameHeight() }, getRect());
}

void FramedImage::initComponent() {
    transform = ent_->getComponent<Transform>();
}