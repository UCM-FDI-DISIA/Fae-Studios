#include "Slider.h"
#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"

void SliderNeedle::initComponent() {
    transform = ent_->getComponent<Transform>();
    texture = ent_->getComponent<FramedImage>();
}

float SliderNeedle::move() {
    SDL_Point mousePosition;
    Vector2D newPos;
    SDL_GetMouseState(&mousePosition.x, &mousePosition.y);
    Vector2D travel = maximumPosition - minimumPosition;
    float range = maxValue - minValue;
    float increment = travel.getX() / range;
    if(mousePosition.x <= maximumPosition.getX() && mousePosition.x >= minimumPosition.getX()) {
        newPos = Vector2D(mousePosition.x, transform->getPosition().getY());
        transform->setPosition(newPos);
    }
    return (newPos - minimumPosition).getX() / increment;
}

void Slider::initComponent() {
    needle = ent_->getComponent<SliderNeedle>();
    transform = ent_->getComponent<Transform>();
    texture = ent_->getComponent<FramedImage>();
    title = ent_->getComponent<Text>();
    percentageText = ent_->getComponent<SliderPercentage>();
}

void Slider::handleInput() {
    SDL_Point mousePosition;
    SDL_Rect sliderRect = { (int)transform->getPosition().getX(), (int)transform->getPosition().getY(), (int)transform->getWidth(), (int)transform->getHeight() };
    SDL_GetMouseState(&mousePosition.x, &mousePosition.y); //Nos guardamos la posición del ratón
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
        currentValue = this->needle->move();
        onChange();
    }

}

void Slider::onChange() {
    callback(currentValue);
}