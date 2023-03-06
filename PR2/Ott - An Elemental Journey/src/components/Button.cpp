#include "Button.h"
#include "../ecs/Entity.h"
#include "../utils/Vector2D.h"
#include "../sdlutils/InputHandler.h"

void Button::initComponent() {
	transform = ent_->getComponent<Transform>();
	texture = ent_->getComponent<FramedImage>();
	text = ent_->getComponent<Text>();
}

void Button::handleInput() {
    SDL_Point mousePosition;
    SDL_Rect buttonRect = { transform->getPosition().getX(), transform->getPosition().getY(), transform->getWidth(), transform->getHeight() };
    Vector2D position = transform->getPosition();
    SDL_GetMouseState(&mousePosition.x, &mousePosition.y); //Nos guardamos la posición del ratón
    //Si clicamos en el botón, llamamos a su onClick
    if (!SDL_PointInRect(&mousePosition, &buttonRect)) {
        Vector2D textPosition = Vector2D((transform->getWidth() - text->getWidth()) / 2, (transform->getHeight() - text->getHeight()) / 2);
        text->setPosition(textPosition);
        currentButtonFrame = MOUSE_OUT; //Indica que el ratón ha salido de la posición del botón
    }
    if (SDL_PointInRect(&mousePosition, &buttonRect)) {
        Vector2D textPosition = Vector2D((transform->getWidth() - text->getWidth()) / 2, (transform->getHeight() - text->getHeight()) / 2);
        text->setPosition(textPosition);
        currentButtonFrame = MOUSE_OVER; //Indica que el ratón está sobre el botón
    }
    if (SDL_PointInRect(&mousePosition, &buttonRect) && InputHandler::instance()->getMouseButtonState(InputHandler::LEFT)) { //Indica que se ha pulsado el botón
        currentButtonFrame = CLICKED;
        Vector2D textPosition = Vector2D((transform->getWidth() - text->getWidth()) / 2, (transform->getHeight() - text->getHeight()) / 2);
        text->setPosition(textPosition);
        onClick(); //Si clicamos, llamamos a la función asociada al botón
    }
}

void Button::onClick() {
    InputHandler::instance()->clearState(true);
    callback();
}