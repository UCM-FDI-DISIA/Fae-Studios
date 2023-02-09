#pragma once

#include "../MenuState.h"
#include "../../../ui/Text.h"

class OptionsMenuState : public MenuState {
private:
	static void musicOptions(SDLApplication* app);
	static void graphicOptions(SDLApplication* app);
	static void controls(SDLApplication* app);
	static void back(SDLApplication* app);
	Text* titleBack = nullptr;
    Text* titleFront= nullptr;

public:
	OptionsMenuState(SDLApplication* app);
	void render() const final;
	~OptionsMenuState() override;
};

