#pragma once
#include "MenuState.h"
#include "../../ui/Text.h"

class MainMenuState : public MenuState {
private:
    Text* titleBack = nullptr;
    Text* titleFront = nullptr;
	Text* faeStudiosBack = nullptr;
	Text* faeStudiosFront = nullptr;
	Text* versionBack = nullptr;
	Text* versionFront = nullptr;

	static void play(SDLApplication* app);
	static void loadSave(SDLApplication* app);
	static void options(SDLApplication* app);
	static void quit(SDLApplication* app);

public:
	MainMenuState(SDLApplication* app);
    void render() const final;
    ~MainMenuState() override;
};

