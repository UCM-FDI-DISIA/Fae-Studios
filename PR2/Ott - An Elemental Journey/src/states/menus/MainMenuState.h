#pragma once
#include "MenuState.h"
//#include "../../ui/UIText.h"
#include "../PlayState.h"

const float MAIN_MENU_OTT_ANIM_TIME = 400;

class MainMenuState : public MenuState {
private:
    /*UIText* titleBack = nullptr;
    UIText* titleFront = nullptr;
	UIText* faeStudiosBack = nullptr;
	UIText* faeStudiosFront = nullptr;
	UIText* versionBack = nullptr;
	UIText* versionFront = nullptr;*/
	
	/*Texture* littleOtt = nullptr;
	SDL_Rect littleOttRect;
	Vector2D littleOttPos;
	Uint8 animFrame = 0;
	float animTime = 0;*/

	static void play();
	//static void loadSave();
	static void options();
	static void quit();

public:
	MainMenuState();
    void render() const final;
	void update() final;
};

