#pragma once
#include "MenuState.h"
#include "../../ui/Text.h"

const float MAIN_MENU_OTT_ANIM_TIME = 400;

class MainMenuState : public MenuState {
private:
    Text* titleBack = nullptr;
    Text* titleFront = nullptr;
	Text* faeStudiosBack = nullptr;
	Text* faeStudiosFront = nullptr;
	Text* versionBack = nullptr;
	Text* versionFront = nullptr;
	
	Texture* littleOtt = nullptr;
	SDL_Rect littleOttRect;
	Vector2D littleOttPos;
	uint animFrame = 0;
	float animTime = 0;

	static void play(SDLApplication* app);
	static void loadSave(SDLApplication* app);
	static void options(SDLApplication* app);
	static void quit(SDLApplication* app);

public:
	MainMenuState(SDLApplication* app);
    void render() const final;
    ~MainMenuState() override;
	void update() final;
};

