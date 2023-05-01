#pragma once
#include "MenuState.h"
#include <vector>
#include "../PlayState.h"

const float MAIN_MENU_OTT_ANIM_TIME = 400;

class MainMenuState : public MenuState {
private:
	Uint8 animFrame = 0;
	float animTime = 0;
    Entity* littleOtt;
	bool playStateInit;
	std::vector<Entity*> buttons;
	int buttonIndex;
	int formerIndex;
	bool detectJoystickActivity;

public:
	MainMenuState();
	void update() final;
	void handleInput() final;
	void changeResolution() override;
};

