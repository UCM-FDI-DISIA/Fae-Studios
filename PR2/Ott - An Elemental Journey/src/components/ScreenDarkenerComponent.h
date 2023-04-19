#pragma once
#ifndef OTT_SCREENDARKENERCOMPONENT_H
#define OTT_SCREENDARKENERCOMPONENT_H

#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include "Transform.h"
#include "../sdlutils/SDLUtils.h"


class ScreenDarkenerComponent : public Component {
private:
    float alpha;
    bool changeAlpha;
    bool isDark;
    Transform* transform_;
    Texture* leftSide;
    Texture* rightSide;
    Texture* topSide;
    Texture* bottomSide;

public:
    constexpr static ecs::cmpId_type id = ecs::_SCREEN_DARKENER;

    ScreenDarkenerComponent() : Component(), alpha(0.0f), changeAlpha(false), isDark(false) {
        leftSide = &sdlutils().images().at("screendarkenside");
        rightSide = &sdlutils().images().at("screendarkenside");
        topSide = &sdlutils().images().at("screendarkentop");
        bottomSide = &sdlutils().images().at("screendarkentop");
    }

    void render() override;

    void update() override;

    void initComponent() override;

    void darken();

    void undarken();
};


#endif //OTT_SCREENDARKENERCOMPONENT_H
