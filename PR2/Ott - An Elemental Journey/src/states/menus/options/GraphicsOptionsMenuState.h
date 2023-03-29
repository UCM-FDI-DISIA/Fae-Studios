#pragma once
#include "../MenuState.h"
#include "../../../sdlutils/SDLUtils.h"
#include "../../../ecs/Entity.h"


class GraphicOptionsMenuState : public MenuState {
private:
	SDLUtils::SCREEN_MODES s = SDLUtils::WINDOWED;
	Entity* fsText;
	Entity* fwText;
	Vector2D fsTextPos;
	Vector2D fwTextPos;
	bool fwNeedChange = false;

public:
	GraphicOptionsMenuState();
	void update() override;
	void changeResolution() override;
};

