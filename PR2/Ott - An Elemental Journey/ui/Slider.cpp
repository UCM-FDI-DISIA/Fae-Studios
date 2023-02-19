#include "../checkML.h"
#include "Slider.h"
#include "../SDLApplication.h"
#include <math.h>
#include "../utils/InputHandler.h"
int Slider::SliderNeedle::move() {
    SDL_Point mousePosition;
    SDL_GetMouseState(&mousePosition.x, &mousePosition.y);
    if ((position.getX() - initialPos.getX()) / 4 <= MAX_VALUE || (position.getX() - initialPos.getX()) / 4 >= MIN_VALUE) {
        if (mousePosition.x <= initialPos.getX() + 4 * (MAX_VALUE) && mousePosition.x >= initialPos.getX() + 4 * MIN_VALUE) {
            position = Vector2D(mousePosition.x, position.getY());
        }
        return ceil((position.getX() - initialPos.getX()) / 4);
    }
}

void Slider::SliderNeedle::render(const SDL_Rect& Camera) const {
    texture->renderFrame(getRect(), 0, currentSliderNeedleFrame);
}

Slider::Slider(const Vector2D& position, Texture* sliderTexture, Texture* needleTexture, const std::string& sliderTitle, SDLApplication* app, 
    SliderCallBack* callback, int initialValue, bool showValue, const Scale& sliderScale, const Scale& needleScale, const Scale& titleScale,
    const SDL_Color& titleColor) : UIElement(position, sliderTexture, sliderScale), app(app), callback(callback), titleScale(titleScale), textColor(titleColor), showValue(showValue), value(initialValue) {
    needle = new SliderNeedle(position + Vector2D(4 * value + 5,-20), position + Vector2D(5,0), needleTexture, needleScale);
    if (showValue) {
        Scale valueScale = Scale(2.0f, 2.0f);
        textValue = new UIText(std::to_string(value) + "%", *(app->getFont("vcr_osd")), position + Vector2D(texture->getW() / 2, 0), app->getRenderer(), {255,255,255}, valueScale);
        textValue->movePosition(Vector2D(position.getX() + (texture->getW() / 2) - (valueScale.widthScale / 2) * textValue->getTexture()->getW(), position.getY() + 0.5 * (textValue->getTexture()->getH() + 2 * (10 * 1 / valueScale.heightScale))));
    }
    title = new UIText(sliderTitle, *(app->getFont("vcr_osd")), position + Vector2D(texture->getW() / 2, 0), app->getRenderer(), textColor, titleScale);
    title->movePosition(Vector2D(position.getX() + (texture->getW() / 2) - (titleScale.widthScale / 2) * title->getTexture()->getW(), position.getY() + 3.5 * (title->getTexture()->getH() + 2 * (10 * 1 / titleScale.heightScale - (10 * titleScale.heightScale)))));
}

Slider::~Slider() {
	delete needle;
	if(showValue) delete textValue;
    delete title;
}

void Slider::handleEvents() {
    SDL_Point mousePosition;
    SDL_Rect sliderRect = getRect();
    SDL_GetMouseState(&mousePosition.x, &mousePosition.y); //Nos guardamos la posici�n del rat�n
    //Si clicamos y arrastramos en el slider, llamamos a su onChange
    if (!SDL_PointInRect(&mousePosition, &sliderRect)) {
        currentSliderFrame = MOUSE_OUT; //Indica que el rat�n ha salido de la posici�n del bot�n
        this->needle->currentSliderNeedleFrame = MOUSE_OUT;
    }
    if (SDL_PointInRect(&mousePosition, &sliderRect)) {
        currentSliderFrame = MOUSE_OVER; //Indica que el rat�n est� sobre el bot�n
        this->needle->currentSliderNeedleFrame = MOUSE_OVER;
    }
    if (SDL_PointInRect(&mousePosition, &sliderRect) && InputHandler::instance()->getMouseButtonState(InputHandler::LEFT)) { //Indica que se ha pulsado el bot�n
        currentSliderFrame = CLICKED;
        clicked = true;
        this->needle->currentSliderNeedleFrame = CLICKED;
    }
    else if (!InputHandler::instance()->getMouseButtonState(InputHandler::LEFT)) {
        clicked = false;
        currentSliderFrame = MOUSE_OVER;
        this->needle->currentSliderNeedleFrame = MOUSE_OVER;
    }
    if (clicked && InputHandler::instance()->mouseMotionEvent()) {
        this->needle->currentSliderNeedleFrame = CLICKED;
        value = this->needle->move();
        onChange();
    }
}

void Slider::update() {
    if (value != previousValue && showValue) {
        UIText* tmp = textValue;
        Scale valueScale = Scale(2.0f, 2.0f);
        textValue = new UIText(std::to_string(value) + "%", *(app->getFont("vcr_osd")), position + Vector2D(texture->getW() / 2, 0), app->getRenderer(), textColor, valueScale);
        textValue->movePosition(position);
        delete tmp;
    }
}

void Slider::render(const SDL_Rect& Camera) const {
    texture->renderFrame(getRect(), currentSliderFrame, 0);
    needle->render();
    if(showValue) textValue->render();
    title->render();
}

void Slider::onChange() {
    callback(value, app);
}