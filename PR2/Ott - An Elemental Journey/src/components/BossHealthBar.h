#pragma once
#include "../sdlutils/Texture.h"
#include <vector>
#include "../ecs/Component.h"
#include "../ecs/Entity.h"

class BossHealthBar : public Component
{
public:
	constexpr static ecs::cmpId_type id = ecs::_HEALTH_IMAGE;
	BossHealthBar(Texture* bar, Texture* life) : barTx(bar), lifeTx(life) {}
	void initComponent() override;
	void damage(int n);
	void reset();
	virtual void render();
private:
	int maxWidth = 0;
	int BossLife = 10;
	int offset = 30;
	Texture* barTx;
	Texture* lifeTx;
	SDL_Rect posBar = {0, 0, 0, 0};
	SDL_Rect posLife = { 0, 0, 0, 0 };
};

