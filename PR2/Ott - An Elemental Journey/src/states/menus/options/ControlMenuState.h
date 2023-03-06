#pragma once
#include "../MenuState.h"
class ControlMenuState : public MenuState {
private:
	static void back();
	//Texture* controles = nullptr;
	//SDL_Rect controlsRect;

public:
	ControlMenuState();
	void render() const final;
};

