#pragma once
#include "../MenuState.h"
class ControlMenuState : public MenuState {
private:
	static void back(SDLApplication* app);
	Texture* controles = nullptr;

public:
	ControlMenuState(SDLApplication* app);
	void render() const final;
};

