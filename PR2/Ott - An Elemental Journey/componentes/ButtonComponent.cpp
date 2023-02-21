#include "ButtonComponent.h"
#include "../SDLApplication.h"
#include "../utils/InputHandler.h"

void ButtonComponent::onClick()
{
	InputHandler::instance()->clearState(true);
	callback(app); //Llamamos a la función callback
}

void ButtonComponent::initComponent()
{
	image = ent_->getComponent<Image>();
}

void ButtonComponent::update() {
    SDL_Point mousePosition;
    SDL_Rect buttonRect = image->getRect();
    SDL_GetMouseState(&mousePosition.x, &mousePosition.y); //Nos guardamos la posición del ratón
    //Si clicamos en el botón, llamamos a su onClick
    if (!SDL_PointInRect(&mousePosition, &buttonRect)) {
        //text->movePosition(Vector2D(position.getX() + ((texture->getW() / 3) / 2) - (textScale.widthScale / 2) * text->getTexture()->getW(), position.getY() + text->getTexture()->getH() + 2 * (10 * 1 / textScale.heightScale)));
        currentButtonFrame = MOUSE_OUT; //Indica que el ratón ha salido de la posición del botón
    }
    if (SDL_PointInRect(&mousePosition, &buttonRect)) {
        //text->movePosition(Vector2D(position.getX() + ((texture->getW() / 3) / 2) - (textScale.widthScale / 2) * text->getTexture()->getW(), position.getY() + text->getTexture()->getH() + 2 * (10 * 1 / textScale.heightScale)));
        currentButtonFrame = MOUSE_OVER; //Indica que el ratón está sobre el botón
    }
    if (SDL_PointInRect(&mousePosition, &buttonRect) && InputHandler::instance()->getMouseButtonState(InputHandler::LEFT)) { //Indica que se ha pulsado el botón
        currentButtonFrame = CLICKED;
        //text->movePosition(Vector2D(position.getX() + ((texture->getW() / 3) / 2) - (textScale.widthScale / 2) * text->getTexture()->getW(), position.getY() + text->getTexture()->getH() + (100 * (1 / textScale.heightScale)) / 2));
        onClick(); //Si clicamos, llamamos a la función asociada al botón
    }
}
