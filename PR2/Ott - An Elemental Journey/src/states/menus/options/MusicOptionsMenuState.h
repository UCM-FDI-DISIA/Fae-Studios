#pragma once
#include "../MenuState.h"


class MusicOptionsMenuState : public MenuState {
private:
	void generalVolume(int value);
	void musicVolume(int value);
	void soundsVolume(int value);
public:
	MusicOptionsMenuState();
};

