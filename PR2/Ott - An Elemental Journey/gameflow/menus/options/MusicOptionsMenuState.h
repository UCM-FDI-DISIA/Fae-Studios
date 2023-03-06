#pragma once
#include "../MenuState.h"


class MusicOptionsMenuState : public MenuState {
private:
	static void generalVolume(int value, SDLApplication* app);
	static void musicVolume(int value, SDLApplication* app);
	static void soundsVolume(int value, SDLApplication* app);
	static void back(SDLApplication* app);
public:
	MusicOptionsMenuState(SDLApplication* app);
};

