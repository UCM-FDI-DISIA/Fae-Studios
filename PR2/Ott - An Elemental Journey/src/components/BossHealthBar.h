#pragma once
#include "../sdlutils/Texture.h"
#include <vector>
#include "../ecs/Component.h"
#include "CameraComponent.h"

class BossHealthBar
{
public:
	constexpr static ecs::cmpId_type id = ecs::_HEALTH_IMAGE;
	BossHealthBar(Texture* bar, Texture* life, SDL_Rect pBar) : barTx(bar), lifeTx(life), posBar(pBar) {

	}
	void damage(int n);
	void reset();
	virtual void render();
private:
	Texture* barTx;
	Texture* lifeTx;
	SDL_Rect posBar;
	SDL_Rect posLife;
};

