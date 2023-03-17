#pragma once
#ifndef TPV2_TEXT_H
#define TPV2_TEXT_H
#include "../ecs/Component.h"
#include "../sdlutils/Font.h"
#include "../sdlutils/Texture.h"
#include "Transform.h"
#include <string>


class TextComponent : public Component{
private:
    Texture* textTexture;
    int x;
    int y;
public:
    constexpr static ecs::cmpId_type id = ecs::_TEXT;
    TextComponent(std::string text, Font& f, SDL_Color fontColor, SDL_Color bgColor);
    virtual ~TextComponent() {delete textTexture;}
    void render() override;
    int getWidth() const {return textTexture->width();}
    int getHeight() const {return textTexture->height();}
    inline void setPosition(Vector2D& v) {x = v.getX(); y = v.getY();}
    inline Vector2D getPosition() const { return Vector2D(x, y); }
};


#endif //TPV2_TEXT_H
