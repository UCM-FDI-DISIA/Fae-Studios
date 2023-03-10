#include "../checkML.h"
#include "GameObject.h"
#include "../gameflow/GameState.h"

GameObject::GameObject(const Vector2D& position, Texture* texture, const Scale& scale, GO_TYPE type) {
    this->position = position;
    this->texture = texture;
    this->width = texture->getW() / texture->getNumCols() * scale.widthScale;
    this->height = texture->getH() / texture->getNumRows() * scale.heightScale;
    this->type = type;
}

GO_TYPE GameObject::getType() { return type; }

SDL_Rect GameObject::getRect() const {
    SDL_Rect destRect;
    destRect.x = position.getX(); destRect.y = position.getY();
    destRect.h = height; destRect.w = width;
    return destRect; //Devolvemos un rectángulo con la posición del objeto en pantalla, su anchura y su altura
}

void GameObject::render(const SDL_Rect& Camera) const {
    SDL_Rect rect = getRect();
    rect.x -= Camera.x;
    rect.y -= Camera.y;
    texture->render(rect);
}