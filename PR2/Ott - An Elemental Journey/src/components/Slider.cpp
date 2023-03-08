#include "Slider.h"
#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include <math.h>

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
    if (mousePosition.x <= maximumPosition.getX() && mousePosition.x >= minimumPosition.getX()) {
        newPos = Vector2D(mousePosition.x, transform->getPosition().getY());
        transform->setPosition(newPos);
        return (newPos - minimumPosition).getX() / increment;
    }
    else if (mousePosition.x > maximumPosition.getX()) return maxValue;
    else if (mousePosition.x < minimumPosition.getX()) return minValue;

}

SliderPercentage::SliderPercentage(std::string text, Font& f, SDL_Color fontColor, SDL_Color bgColor) : f(f), fontColor(fontColor), bgColor(bgColor) {
    x = 0;
    y = 0;
    textTexture = createTexture(text, this->f, this->fontColor, this->bgColor);
}

Texture* SliderPercentage::createTexture(std::string text, Font& f, SDL_Color fontColor, SDL_Color bgColor) {
    //Mac renderiza el texto de diferente manera que Windows, por tanto hacemos esa distinción aquí
#ifdef __APPLE__
    return new Texture(sdlutils().renderer(), text, f, fontColor, bgColor);
#endif

#ifdef __WINDOWS__
    if (bgColor.a <= 1) return new Texture(sdlutils().renderer(), text, f, fontColor);
    else return new Texture(sdlutils().renderer(), text, f, fontColor, bgColor);
#endif
}

void SliderPercentage::render() {
    textTexture->render(x, y);
}

void SliderPercentage::changeText(std::string text) {
    delete textTexture;
    textTexture = createTexture(text, this->f, this->fontColor, this->bgColor);
}

void Slider::initComponent() {
    transform = ent_->getComponent<Transform>();
    texture = ent_->getComponent<FramedImage>();
    title = ent_->getComponent<Text>();
    percentageText = ent_->getComponent<SliderPercentage>();
}

void Slider::handleInput() {
    SDL_Point mousePosition;
    SDL_Rect sliderRect = { (int)transform->getPosition().getX(), (int)transform->getPosition().getY(), (int)transform->getWidth(), (int)transform->getHeight() };
    SDL_GetMouseState(&mousePosition.x, &mousePosition.y); //Nos guardamos la posición del ratón
    SliderNeedle* n = needle->getComponent<SliderNeedle>();
    //Si clicamos y arrastramos en el slider, llamamos a su onChange
    if (!SDL_PointInRect(&mousePosition, &sliderRect)) {
        currentSliderFrame = MOUSE_OUT; //Indica que el rat�n ha salido de la posici�n del bot�n
        n->currentSliderNeedleFrame = MOUSE_OUT;
    }
    if (SDL_PointInRect(&mousePosition, &sliderRect)) {
        currentSliderFrame = MOUSE_OVER; //Indica que el rat�n est� sobre el bot�n
        n->currentSliderNeedleFrame = MOUSE_OVER;
    }
    if (SDL_PointInRect(&mousePosition, &sliderRect) && InputHandler::instance()->getMouseButtonState(InputHandler::LEFT)) { //Indica que se ha pulsado el bot�n
        currentSliderFrame = CLICKED;
        clicked = true;
        n->currentSliderNeedleFrame = CLICKED;
    }
    else if (!InputHandler::instance()->getMouseButtonState(InputHandler::LEFT)) {
        clicked = false;
        currentSliderFrame = MOUSE_OVER;
        n->currentSliderNeedleFrame = MOUSE_OVER;
    }
    if (clicked && InputHandler::instance()->mouseMotionEvent()) {
        n->currentSliderNeedleFrame = CLICKED;
        currentValue = n->move();
        onChange();
    }

    texture->setRow(currentSliderFrame);
    n->getTexture()->setCol(n->currentSliderNeedleFrame);
    
    std::string valueText = std::to_string((int)std::ceil(currentValue)) + "%";
    percentageText->changeText(valueText);
    Vector2D percentagePosition = Vector2D(transform->getPosition().getX() + (transform->getWidth() - percentageText->getWidth()) / 2, transform->getPosition().getY() + (transform->getHeight() - percentageText->getHeight()) / 2 - 5);
    percentageText->setPosition(percentagePosition);
}

void Slider::onChange() {
    callback(currentValue);
}

void Slider::setNeedle(Entity* needle) {
    this->needle = needle;
    Vector2D needlePos = transform->getPosition() - Vector2D((this->needle->getComponent<FramedImage>()->getFrameWidth() / 2.5f) / 2, (this->needle->getComponent<FramedImage>()->getFrameHeight() / 2.5f) / 2 + 10);
    this->needle->getComponent<SliderNeedle>()->setPosition(needlePos);
    Vector2D maxNeedlePos = needlePos + Vector2D(texture->getFrameWidth(), 0);
    this->needle->getComponent<SliderNeedle>()->setLimitPositions(needlePos, maxNeedlePos);
    this->needle->getComponent<SliderNeedle>()->setMaxValue(getMaxValue());
    this->needle->getComponent<SliderNeedle>()->setMinValue(getMinValue());
    
    Vector2D titlePosition = Vector2D(transform->getPosition().getX() + (transform->getWidth() - title->getWidth()) / 2, transform->getPosition().getY() - (transform->getHeight() - title->getHeight()) * 2);
    Vector2D percentagePosition = Vector2D(transform->getPosition().getX() + (transform->getWidth() - percentageText->getWidth()) / 2, transform->getPosition().getY() + (transform->getHeight() - percentageText->getHeight()) / 2 - 5);
    title->setPosition(titlePosition);
    percentageText->setPosition(percentagePosition);
}