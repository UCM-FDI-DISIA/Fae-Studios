#pragma once
#include "MenuState.h"

class PauseMenuState : public MenuState {
private:
	static void resume();
	static void mainMenu();
	static void settings();
	static void exit();

public:
	PauseMenuState();

	void handleInput() override;
};

