#pragma once
#include "../ecs/Component.h"
#include "Transform.h"
#include "FramedImage.h"
#include "TextComponent.h"

using SliderCallback = void(int value);

enum slider_State { MOUSE_OUT = 0, MOUSE_OVER = 1, CLICKED = 2 };

class SliderNeedle : public Component {
private:
    Transform* transform;
    FramedImage* texture;
    Vector2D minimumPosition;
    Vector2D maximumPosition;
    float maxValue;
    float minValue;

public:
    slider_State currentSliderNeedleFrame;
    constexpr static ecs::cmpId_type id = ecs::_SLIDER_NEEDLE;
    SliderNeedle() : Component() {
        transform = nullptr;
        texture = nullptr;
        maxValue = 100.0f;
        minValue = 0.0f;
        currentSliderNeedleFrame = MOUSE_OUT;
    };
    virtual ~SliderNeedle() = default;
    void initComponent() override;
    float move();
    void setPosition(Vector2D& v) {transform->setPosition(v);}
    void setLimitPositions(Vector2D& minimum, Vector2D& maximum) {minimumPosition = minimum; maximumPosition = maximum; }
    void setMaxValue(float f) {maxValue = f;}
    void setMinValue(float f) {minValue = f;}
    FramedImage* getTexture() { return texture; }
};

class SliderPercentage : public Component {
private:
    Texture* textTexture;
    int x;
    int y;
    Font& f;
    SDL_Color fontColor;
    SDL_Color bgColor;

    Texture* createTexture(std::string text, Font& f, SDL_Color fontColor, SDL_Color bgColor);
public:
    constexpr static ecs::cmpId_type id = ecs::_SLIDER_PERCENTAGE;
    SliderPercentage(std::string text, Font& f, SDL_Color fontColor, SDL_Color bgColor);
    virtual ~SliderPercentage() { delete textTexture; }
    void render() override;
    int getWidth() const { return textTexture->width(); }
    int getHeight() const { return textTexture->height(); }
    inline void setPosition(Vector2D& v) { x = v.getX(); y = v.getY(); }
    inline Vector2D getPosition() const { return Vector2D(x, y); }
    void changeText(std::string text);
};

class Slider : public Component {
private:
    /// Estados en los que puede estar la textura de un slider
    Entity* needle;
    SliderCallback* callback;
    Transform* transform;
    FramedImage* texture;
    TextComponent* title;
    SliderPercentage* percentageText;
    float currentValue;
    float maxValue;
    float minValue;
    slider_State currentSliderFrame;
    bool clicked;

    void onChange();

public:
    constexpr static ecs::cmpId_type id = ecs::_SLIDER;
    Slider(float maxValue, float minValue, float initialValue, SliderCallback* callback) : Component(), maxValue(maxValue), minValue(minValue), currentValue(initialValue), callback(callback) {
        needle = nullptr;
        transform = nullptr;
        texture = nullptr;
        title = nullptr;
        percentageText = nullptr;
        currentSliderFrame = MOUSE_OUT;
        clicked = false;
    }
    virtual ~Slider() = default;
    void initComponent() override;
    void handleInput() override;
    void setNeedle(Entity* needle);
    float getMaxValue() const { return maxValue; }
    float getMinValue() const { return minValue; }
};

