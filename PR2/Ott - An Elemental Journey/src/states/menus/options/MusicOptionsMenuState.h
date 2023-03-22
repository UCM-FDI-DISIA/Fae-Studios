#pragma once
#include "../MenuState.h"


class MusicOptionsMenuState : public MenuState {
private:
	void generalVolume(int value);
	void musicVolume(int value);
	void soundsVolume(int value);
	void uiVolume(int value);

public:
	MusicOptionsMenuState();
};

