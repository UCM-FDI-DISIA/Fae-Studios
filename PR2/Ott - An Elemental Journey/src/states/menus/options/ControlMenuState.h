#pragma once
#include "../MenuState.h"
class ControlMenuState : public MenuState {
private:
	std::vector<Entity*> buttons;
	int buttonIndex;
	int formerIndex;
	bool detectJoystickActivity;

public:
	ControlMenuState();
	void handleInput() override;
};

