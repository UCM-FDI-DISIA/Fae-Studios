#pragma once
#include "../MenuState.h"


class MusicOptionsMenuState : public MenuState {
private:
	void musicVolume(int value);
	void uiVolume(int value);
	void playerVolume(int value);
	void enemiesVolume(int value);
	void miscVolume(int value);
	void masterVolume(int value);

	std::vector<Entity*> buttons;
	int buttonIndex;
	int formerIndex;
	bool detectJoystickActivity;

public:
	MusicOptionsMenuState();
	void handleInput() override;
};

