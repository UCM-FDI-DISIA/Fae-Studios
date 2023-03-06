#pragma once

#include "../MenuState.h"
//#include "../../../ui/UIText.h"

class OptionsMenuState : public MenuState {
private:
	static void musicOptions();
	static void graphicOptions();
	static void controls();
	static void back();

public:
	OptionsMenuState();
};

