#include "ScreenDarkener.h"
#include "../SDLApplication.h"

ScreenDarkener::ScreenDarkener(SDLApplication* app) : UIElement() {
   rightSide = leftSide = app->getTexture("screendarkenside", PLAY_STATE);
    bottomSide = topSide = app->getTexture("screendarkentop", PLAY_STATE);
    mustShow = false;
    LsRect = {0, 0, leftSide->getW(), leftSide->getH()};
    TsRect = {0,0, topSide->getW(), topSide->getH()};
    int rsRectPosX = WINDOW_WIDTH - rightSide->getW();
    RsRect = {rsRectPosX, 0, rightSide->getW(), rightSide->getH()};
    int bsRectPosY = WINDOW_HEIGHT - bottomSide->getH();
    BsRect = {0, bsRectPosY, bottomSide->getW(), bottomSide->getH()};
}

void ScreenDarkener::render(const SDL_Rect& camera) const {
    if(mustShow) {
        rightSide->render(RsRect);
        leftSide->render(LsRect);
        bottomSide->render(BsRect);
        topSide->render(TsRect);
    }
}

void ScreenDarkener::show() {
    mustShow = true;
}

void ScreenDarkener::hide() {
    mustShow = false;
}