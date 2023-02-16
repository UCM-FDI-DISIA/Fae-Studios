#pragma once

#include "../MenuState.h"
#include "../../../ui/UIText.h"

class OptionsMenuState : public MenuState {
private:
	static void musicOptions(SDLApplication* app);
	static void graphicOptions(SDLApplication* app);
	static void controls(SDLApplication* app);
	static void back(SDLApplication* app);
	UIText* titleBack = nullptr;
    UIText* titleFront= nullptr;

public:
	OptionsMenuState(SDLApplication* app);
	virtual void render() const;
	~OptionsMenuState() override;
};

