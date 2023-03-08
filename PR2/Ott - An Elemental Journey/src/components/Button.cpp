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
    SDL_Rect buttonRect = { (int)transform->getPosition().getX(), (int)transform->getPosition().getY(), (int)transform->getWidth(), (int)transform->getHeight() };
    Vector2D position = transform->getPosition();
    Vector2D textPosition;
    SDL_GetMouseState(&mousePosition.x, &mousePosition.y); //Nos guardamos la posici�n del rat�n
    //Si clicamos en el bot�n, llamamos a su onClick
    if (!SDL_PointInRect(&mousePosition, &buttonRect)) {
        textPosition = Vector2D(transform->getPosition().getX() + (transform->getWidth() - text->getWidth())/2, transform->getPosition().getY() + (transform->getHeight() - text->getHeight())/2 - 10);
        currentButtonFrame = MOUSE_OUT; //Indica que el rat�n ha salido de la posici�n del bot�n
    }
    if (SDL_PointInRect(&mousePosition, &buttonRect)) {
        textPosition = Vector2D(transform->getPosition().getX() + (transform->getWidth() - text->getWidth())/2, transform->getPosition().getY() + (transform->getHeight() - text->getHeight())/2 - 10);
        currentButtonFrame = MOUSE_OVER; //Indica que el rat�n est� sobre el bot�n
    }
    if (SDL_PointInRect(&mousePosition, &buttonRect) && InputHandler::instance()->getMouseButtonState(InputHandler::LEFT)) { //Indica que se ha pulsado el bot�n
        currentButtonFrame = CLICKED;
        textPosition = Vector2D(transform->getPosition().getX() + (transform->getWidth() - text->getWidth())/2, transform->getPosition().getY() + (transform->getHeight() - text->getHeight())/2);
        onClick(); //Si clicamos, llamamos a la funci�n asociada al bot�n
    }

    texture->setCol(currentButtonFrame);
    text->setPosition(textPosition);
}

void Button::onClick() {
    InputHandler::instance()->clearState(true);
    callback();
}