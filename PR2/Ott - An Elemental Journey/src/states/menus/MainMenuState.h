#pragma once
#include "MenuState.h"
//#include "../../ui/UIText.h"
#include "../PlayState.h"

const float MAIN_MENU_OTT_ANIM_TIME = 400;

class MainMenuState : public MenuState {
private:
	Uint8 animFrame = 0;
	float animTime = 0;
    Entity* littleOtt;

public:
	MainMenuState();
	void update() final;
};

