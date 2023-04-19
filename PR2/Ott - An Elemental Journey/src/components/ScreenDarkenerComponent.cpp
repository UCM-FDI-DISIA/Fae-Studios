#include "../utils/checkML.h"
#include "ScreenDarkenerComponent.h"

void ScreenDarkenerComponent::render() {
    SDL_Rect tmp;
    tmp = {transform_->getRect().x, transform_->getRect().y, leftSide->width(), leftSide->height()};
    leftSide->render(tmp);
    tmp = {(int)(sdlutils().getWindowDimensions().getX() - rightSide->width()), transform_->getRect().y, rightSide->width(), rightSide->height()};
    rightSide->render(tmp);
    tmp = {transform_->getRect().x + leftSide->width(), transform_->getRect().y, topSide->width() - rightSide->width(), topSide->height()};
    topSide->render(tmp);
    tmp = {transform_->getRect().x + leftSide->width(), (int)(sdlutils().getWindowDimensions().getY() - bottomSide->height()), bottomSide->width() - rightSide->width(), bottomSide->height()};
    bottomSide->render(tmp);
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

    leftSide->setAlpha(alpha);
    topSide->setAlpha(alpha);
    bottomSide->setAlpha(alpha);
    rightSide->setAlpha(alpha);
}

void ScreenDarkenerComponent::darken() {
    if(!isDark) changeAlpha = true;
}

void ScreenDarkenerComponent::undarken() {
    if(isDark) changeAlpha = true;
}