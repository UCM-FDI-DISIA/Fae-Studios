#pragma once

#include "../MenuState.h"
//#include "../../../ui/UIText.h"

class OptionsMenuState : public MenuState {
private:
	std::vector<Entity*> buttons;
	int buttonIndex;
	int formerIndex;
	bool detectJoystickActivity;

public:
	OptionsMenuState();
	void handleInput() override;
    void changeResolution() override;
};

