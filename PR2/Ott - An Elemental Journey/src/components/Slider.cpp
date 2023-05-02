#include "Slider.h"
#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include <math.h>

void SliderSelectionNeedle::initComponent() {
    transform = ent_->getComponent<Transform>();
    texture = ent_->getComponent<Image>();
}


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

float SliderNeedle::calculateValueOnPositionChange() {
    Vector2D travel = maximumPosition - minimumPosition;
    float range = maxValue - minValue;
    float increment = travel.getX() / range;
    return (transform->getPosition() - minimumPosition).getX() / increment;
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
    title = ent_->getComponent<TextComponent>();
    percentageText = ent_->getComponent<SliderPercentage>();

    Vector2D titlePosition = Vector2D(transform->getPosition().getX() + (transform->getWidth() - title->getWidth()) / 2, transform->getPosition().getY() - (transform->getHeight() - title->getHeight()) * 2);
    Vector2D percentagePosition = Vector2D(transform->getPosition().getX() + (transform->getWidth() - percentageText->getWidth()) / 2, transform->getPosition().getY() + (transform->getHeight() - percentageText->getHeight()) / 2 - 5);
    title->setPosition(titlePosition);
    percentageText->setPosition(percentagePosition);
}

void Slider::handleInput() {
    SDL_Point mousePosition;
    SDL_Rect sliderRect = { (int)transform->getPosition().getX() - 20, (int)transform->getPosition().getY(), (int)transform->getWidth() + 20, (int)transform->getHeight() };
    SDL_GetMouseState(&mousePosition.x, &mousePosition.y); //Nos guardamos la posición del ratón
    SliderNeedle* n = needle->getComponent<SliderNeedle>();
    //Si clicamos y arrastramos en el slider, llamamos a su onChange
    
    if (!SDL_PointInRect(&mousePosition, &sliderRect)) {
        currentSliderFrame = MOUSE_OUT; //Indica que el rat�n ha salido de la posici�n del bot�n
        n->currentSliderNeedleFrame = MOUSE_OUT;
        clicked = false;
    }

    if (SDL_PointInRect(&mousePosition, &sliderRect) && !InputHandler::instance()->getMouseButtonState(InputHandler::LEFT)) {
        currentSliderFrame = MOUSE_OVER; //Indica que el rat�n est� sobre el bot�n
        n->currentSliderNeedleFrame = MOUSE_OVER;
        clicked = false;
    }

    if (SDL_PointInRect(&mousePosition, &sliderRect) && InputHandler::instance()->getMouseButtonState(InputHandler::LEFT)) { //Indica que se ha pulsado el bot�n
        currentSliderFrame = CLICKED;
        clicked = true;
        n->currentSliderNeedleFrame = CLICKED;
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
    Vector2D initialPos = (transform->getPosition() - Vector2D((this->needle->getComponent<FramedImage>()->getFrameWidth() / 2.5f) / 2, (this->needle->getComponent<FramedImage>()->getFrameHeight() / 2.5f) / 2 + 10));
    Vector2D needlePos = initialPos + Vector2D(currentValue * ((texture->getFrameWidth())/(maxValue - minValue)), 0);
    this->needle->getComponent<SliderNeedle>()->setInitialPosition(needlePos);
    Vector2D maxNeedlePos = initialPos + Vector2D(texture->getFrameWidth(), 0);
    this->needle->getComponent<SliderNeedle>()->setLimitPositions(initialPos, maxNeedlePos);
    this->needle->getComponent<SliderNeedle>()->setMaxValue(getMaxValue());
    this->needle->getComponent<SliderNeedle>()->setMinValue(getMinValue());
}

void Slider::update() {
    if (!selected) {
        if (selectionNeedle != nullptr) selectionNeedle->getComponent<SliderSelectionNeedle>()->hide();
    }
    else {
        if (selectionNeedle != nullptr) selectionNeedle->getComponent<SliderSelectionNeedle>()->show();
    }
}

void Slider::setSelectionNeedle(Entity* needle) {
    selectionNeedle = needle;
    Vector2D position = transform->getPosition() + Vector2D(-50, transform->getHeight() / 2 - needle->getComponent<Transform>()->getHeight() / 2);
    selectionNeedle->getComponent<SliderSelectionNeedle>()->setPosition(position);
}

void Slider::setValueInSelection(Vector2D& position) {
    needle->getComponent<SliderNeedle>()->setPosition(position);
    
    currentValue = needle->getComponent<SliderNeedle>()->calculateValueOnPositionChange();
    
    std::string valueText = std::to_string((int)std::ceil(currentValue)) + "%";
    percentageText->changeText(valueText);
    Vector2D percentagePosition = Vector2D(transform->getPosition().getX() + (transform->getWidth() - percentageText->getWidth()) / 2, transform->getPosition().getY() + (transform->getHeight() - percentageText->getHeight()) / 2 - 5);
    percentageText->setPosition(percentagePosition);

    callback(currentValue);
}