#include "Button.h"
#include "../ecs/Entity.h"
#include "../utils/Vector2D.h"
#include "../sdlutils/InputHandler.h"
#include "../utils/checkML.h"

void Button::initComponent() {
	transform = ent_->getComponent<Transform>();
	texture = ent_->getComponent<FramedImage>();
	text = ent_->getComponent<TextComponent>();
}

void Button::handleInput() {
    SDL_Point mousePosition;
    SDL_Rect buttonRect = { (int)transform->getPosition().getX(), (int)transform->getPosition().getY(), (int)transform->getWidth(), (int)transform->getHeight() };
    Vector2D position = transform->getPosition();
    Vector2D textPosition;
    SDL_GetMouseState(&mousePosition.x, &mousePosition.y); //Nos guardamos la posición del ratón
    //Si clicamos en el botón, llamamos a su onClick
    if (!SDL_PointInRect(&mousePosition, &buttonRect)) {
        textPosition = Vector2D(transform->getPosition().getX() + (transform->getWidth() - text->getWidth())/2, transform->getPosition().getY() + (transform->getHeight() - text->getHeight())/2 - 10);
        texture->setCol(currentButtonFrame);
        text->setPosition(textPosition);
        currentButtonFrame = MOUSE_OUT; //Indica que el ratón ha salido de la posición del botón
    }

    if (SDL_PointInRect(&mousePosition, &buttonRect) && (currentButtonFrame == MOUSE_OUT || currentButtonFrame == MOUSE_OVER)) {
        textPosition = Vector2D(transform->getPosition().getX() + (transform->getWidth() - text->getWidth())/2, transform->getPosition().getY() + (transform->getHeight() - text->getHeight())/2 - 10);
        texture->setCol(currentButtonFrame);
        text->setPosition(textPosition);
        currentButtonFrame = MOUSE_OVER; //Indica que el ratón está sobre el botón
    }

    if (SDL_PointInRect(&mousePosition, &buttonRect) && InputHandler::instance()->getMouseButtonState(InputHandler::LEFT)) { //Indica que se ha pulsado el bot�n
        currentButtonFrame = CLICKED;
        textPosition = Vector2D(transform->getPosition().getX() + (transform->getWidth() - text->getWidth())/2, transform->getPosition().getY() + (transform->getHeight() - text->getHeight())/2);
        texture->setCol(currentButtonFrame);
        text->setPosition(textPosition);
    }

    if (SDL_PointInRect(&mousePosition, &buttonRect) && currentButtonFrame == CLICKED && !InputHandler::instance()->getMouseButtonState(InputHandler::LEFT)) {
        currentButtonFrame = MOUSE_OVER;
        textPosition = Vector2D(transform->getPosition().getX() + (transform->getWidth() - text->getWidth()) / 2, transform->getPosition().getY() + (transform->getHeight() - text->getHeight()) / 2 - 10);
        texture->setCol(currentButtonFrame);
        text->setPosition(textPosition);
        onClick(); //Si clicamos, llamamos a la funci�n asociada al bot�n
    }
}

void Button::onClick() {
    InputHandler::instance()->clearState(true);
    callback();
}