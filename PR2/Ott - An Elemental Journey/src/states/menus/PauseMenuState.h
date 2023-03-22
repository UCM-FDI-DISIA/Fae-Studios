#pragma once
#include "MenuState.h"

class PauseMenuState : public MenuState {
public:
	PauseMenuState();

	void handleInput() override;
};

