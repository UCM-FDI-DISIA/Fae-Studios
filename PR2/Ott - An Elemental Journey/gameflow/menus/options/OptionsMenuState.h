#pragma once

#include "../MenuState.h"
#include "../../../ui/Text.h"

class OptionsMenuState : public MenuState {
private:
	static void musicOptions(SDLApplication* app);
	static void graphicOptions(SDLApplication* app);
	static void back(SDLApplication* app);
	Text* title = nullptr;

public:
	OptionsMenuState(SDLApplication* app);
	void render() const final;
	~OptionsMenuState() override;
};

