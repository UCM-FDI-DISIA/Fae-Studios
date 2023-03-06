#pragma once
#include "Transform.h"
#include "../sdlutils/SoundEffect.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../game/Game.h"
class Game;

class Gun : public Component
{
private:
	Transform* transform;
	bool canShot;
	int startTime;
public:
	constexpr static ecs::cmpId_type id = ecs::_GUN;
	Gun() : Component() {
		canShot = true;
		startTime = SDL_GetTicks();
		transform = nullptr;
	}
	void initComponent() override;
	void update() override;
	void handleInput() override;
};

