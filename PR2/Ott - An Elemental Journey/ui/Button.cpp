#include "../checkML.h"
#include "Button.h"
#include "../SDLApplication.h"
#include "../utils/InputHandler.h"

Button::Button(const ButtonParams& params) : UIElement(params.position, params.texture, params.scale), app(params.app), callback(params.callback), buttonText(params.buttonText), textScale(params.textScale) {
    text = new UIText(buttonText, *(app->getFont("vcr_osd")), Vector2D(position.getX() + (texture->getW() / 3 / 2), position.getY()), app->getRenderer(), params.textCol, textScale);
    text->movePosition(Vector2D(position.getX(), position.getY()));
}

Button::~Button() {
    delete text;
}

void Button::handleEvents() {
    SDL_Point mousePosition;
    SDL_Rect buttonRect = getRect();
    SDL_GetMouseState(&mousePosition.x, &mousePosition.y); //Nos guardamos la posición del ratón
    //Si clicamos en el botón, llamamos a su onClick
    if (!SDL_PointInRect(&mousePosition, &buttonRect)) {
        text->movePosition(Vector2D(position.getX() + ((texture->getW() / 3) / 2) - (textScale.widthScale / 2) * text->getTexture()->getW(), position.getY() + text->getTexture()->getH() + 2 * (10 * 1/textScale.heightScale)));
        currentButtonFrame = MOUSE_OUT; //Indica que el ratón ha salido de la posición del botón
    }
    if (SDL_PointInRect(&mousePosition, &buttonRect)) {
        text->movePosition(Vector2D(position.getX() + ((texture->getW() / 3) / 2) - (textScale.widthScale / 2) * text->getTexture()->getW(), position.getY() + text->getTexture()->getH() + 2 * (10 * 1 / textScale.heightScale)));
        currentButtonFrame = MOUSE_OVER; //Indica que el ratón está sobre el botón
    }
    if(SDL_PointInRect(&mousePosition, &buttonRect) && InputHandler::instance()->getMouseButtonState(InputHandler::LEFT)) { //Indica que se ha pulsado el botón
        currentButtonFrame = CLICKED;
        text->movePosition(Vector2D(position.getX() + ((texture->getW() / 3) / 2) - (textScale.widthScale / 2) * text->getTexture()->getW(), position.getY() + text->getTexture()->getH() + (100 * (1/textScale.heightScale))/2));
        onClick(); //Si clicamos, llamamos a la función asociada al botón
    }
}

void Button::render(const SDL_Rect& camera) const {
    texture->renderFrame(getRect(), 0, currentButtonFrame);
    text->render();
}

void Button::onClick() {
    InputHandler::instance()->clearState(true);
    callback(app); //Llamamos a la función callback
}

ImageButton::ImageButton(const ButtonParams& params, Texture* image, ImageClass imgClass, uint row, uint col) : Button(params), image(image), imgClass(imgClass), row(row), col(col) {
    imagePos = getRect();
    imagePos.x += ((texture->getW() / 6) - 2 * ((image->getW()) / image->getNumCols()) / 2 - 5);
    imagePos.y += (texture->getH() / 2 - 0.5 * (image->getH() / 2));
    imagePos.w /= 2;
    imagePos.h /= 3;
}

void ImageButton::render(const SDL_Rect& camera) const {
    Button::render();
    switch (imgClass) {
        case FULL_IMAGE: image->render(imagePos); break;
        case SPRITESHEET: image->renderFrame(imagePos, row, col); break;
    }
}

void ImageButton::handleEvents() {
    Button::handleEvents();
    switch (currentButtonFrame) {
        case MOUSE_OUT:
            imagePos.y = getRect().y + (texture->getH() / 2 - 0.5 * (image->getH() / 2));
            break;
        case MOUSE_OVER:
            imagePos.y = getRect().y + (texture->getH() / 2 - 0.5 * (image->getH() / 2));
            break;
        case CLICKED:
            imagePos.y = getRect().y + 1.15 * (texture->getH() / 2 - 0.5 * (image->getH() / 2));
            break;
    }
}