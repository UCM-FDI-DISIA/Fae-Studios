#pragma once
#include "../ecs/Component.h"
#include "Transform.h"
#include "FramedImage.h"
#include "TextComponent.h"
#include "Image.h"
#include <functional>


class SliderSelectionNeedle : public Component {
private:
    Transform* transform;
    Image* texture;

public:
    constexpr static ecs::cmpId_type id = ecs::_BUTTON_NEEDLE;
    SliderSelectionNeedle() : Component() {
        transform = nullptr;
        texture = nullptr;
    }
    virtual ~SliderSelectionNeedle() = default;
    inline void setPosition(Vector2D& position) { transform->setPosition(position); };
    void initComponent() override;
    inline void show() { texture->enableRender(); }
    inline void hide() { texture->disableRender(); }
};


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
    inline void setInitialPosition(Vector2D& v) {
        transform->setPosition(v);
    }
    inline void setPosition(Vector2D& v) {
        if (v.getX() >= minimumPosition.getX() && v.getX() <= maximumPosition.getX()) transform->setPosition(v);
    }
    Vector2D getPosition() const { return transform->getPosition(); }
    void setLimitPositions(Vector2D& minimum, Vector2D& maximum) {minimumPosition = minimum; maximumPosition = maximum; }
    void setMaxValue(float f) {maxValue = f;}
    void setMinValue(float f) {minValue = f;}
    float calculateValueOnPositionChange();
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
    Entity* selectionNeedle;
    Transform* transform;
    FramedImage* texture;
    TextComponent* title;
    std::function<void(int)> callback;
    SliderPercentage* percentageText;
    float currentValue;
    float maxValue;
    float minValue;
    slider_State currentSliderFrame;
    bool clicked;
    bool selected;

    void onChange();

public:
    constexpr static ecs::cmpId_type id = ecs::_SLIDER;
    Slider(float maxValue, float minValue, float initialValue, std::function<void(int)> const& callback) : Component(), maxValue(maxValue), minValue(minValue), currentValue(initialValue), callback(callback) {
        needle = nullptr;
        transform = nullptr;
        texture = nullptr;
        title = nullptr;
        percentageText = nullptr;
        currentSliderFrame = MOUSE_OUT;
        clicked = false;
        selectionNeedle = nullptr;
        selected = false;
    }
    virtual ~Slider() = default;
    void initComponent() override;
    void handleInput() override;
    void setNeedle(Entity* needle);
    void setSelectionNeedle(Entity* needle);
    void update() override;
    float getMaxValue() const { return maxValue; }
    float getMinValue() const { return minValue; }
    inline void select() { selected = true; }
    inline void unselect() { selected = false; }
    void setValueInSelection(Vector2D& position);
    inline Vector2D getNeedlePosition() const { return needle->getComponent<SliderNeedle>()->getPosition(); }
};

