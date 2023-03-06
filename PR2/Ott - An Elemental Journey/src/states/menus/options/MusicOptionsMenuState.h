#pragma once
#include "../MenuState.h"


class MusicOptionsMenuState : public MenuState {
private:
	static void generalVolume(int value);
	static void musicVolume(int value);
	static void soundsVolume(int value);
	static void back();
public:
	MusicOptionsMenuState();
};

