#pragma once
#ifndef OTT_SCREENDARKENER_H
#define OTT_SCREENDARKENER_H
#include "UIElement.h"

class SDLApplication;

class ScreenDarkener : public UIElement {
private:
    SDLApplication* app;
    Texture* leftSide;
    Texture* rightSide;
    Texture* topSide;
    Texture* bottomSide;
    bool mustShow;
    SDL_Rect LsRect, RsRect, TsRect, BsRect;

public:
    ScreenDarkener(SDLApplication* app);
    void render(const SDL_Rect& camera = { 0,0,0,0 }) const override;
    void show();
    void hide();
};


#endif //OTT_SCREENDARKENER_H
