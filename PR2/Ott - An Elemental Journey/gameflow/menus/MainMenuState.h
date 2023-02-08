#pragma once
#include "MenuState.h"

class MainMenuState : public MenuState {
private:
	static void play(SDLApplication* app);
	static void loadSave(SDLApplication* app);
	static void options(SDLApplication* app);
	static void quit(SDLApplication* app);

public:
	MainMenuState(SDLApplication* app);
};

