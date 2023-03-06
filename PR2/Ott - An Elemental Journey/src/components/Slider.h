#pragma once
#include "../ecs/Component.h"
#include "Transform.h"
#include "FramedImage.h"
#include "Text.h"
#include "SliderPercentage.h"

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
};

class Slider : public Component {
private:
    /// Estados en los que puede estar la textura de un slider
    SliderNeedle* needle;
    SliderCallback* callback;
    Transform* transform;
    FramedImage* texture;
    Text* title;
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
};

