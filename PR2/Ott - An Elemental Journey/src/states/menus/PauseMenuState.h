#pragma once
#include "MenuState.h"

class PauseMenuState : public MenuState {
private:
	std::vector<Entity*> buttons;
	int buttonIndex;
	int formerIndex;
	bool detectJoystickActivity;

public:
	PauseMenuState();

	void handleInput() override;
};

