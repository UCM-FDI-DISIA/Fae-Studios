#pragma once
#include "MenuState.h"

class PauseMenuState : public MenuState {
private:
	static void resume(SDLApplication* app);
	static void mainMenu(SDLApplication* app);
	static void settings(SDLApplication* app);
	static void exit(SDLApplication* app);

public:
	PauseMenuState(SDLApplication* app);
	virtual void handleEvents();
};

