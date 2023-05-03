#include "../utils/checkML.h"
#include "ScreenDarkenerComponent.h"

void ScreenDarkenerComponent::render() {
    SDL_Rect tmp;
    tmp = {0, 0, sdlutils().width(), sdlutils().height()};

}

void ScreenDarkenerComponent::initComponent() {
    transform_ = ent_->getComponent<Transform>();
}

void ScreenDarkenerComponent::update() {
    if(!isDark && changeAlpha && alpha < 200.0f) alpha += 1.0f;
    if(isDark && changeAlpha && alpha > 0) alpha -= 1.0f;

    if(alpha == 200.0f) {
        isDark = true;
        changeAlpha = false;
    }
    else if(alpha == 0.0f) {
        isDark = false;
        changeAlpha = false;
    }

    img->setAlpha(alpha);
}

void ScreenDarkenerComponent::darken() {
    if(!isDark) changeAlpha = true;
}

void ScreenDarkenerComponent::undarken() {
    if(isDark) changeAlpha = true;
}