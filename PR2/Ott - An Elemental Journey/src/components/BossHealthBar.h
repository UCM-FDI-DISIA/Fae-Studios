#pragma once
#include "../sdlutils/Texture.h"
#include <vector>
#include "../ecs/Component.h"
#include "../ecs/Entity.h"

class BossHealthBar : public Component
{
	enum Boss{Earth = 1, Water = 2, Fire = 3};
public:
	constexpr static ecs::cmpId_type id = ecs::_HEALTH_IMAGE;
	BossHealthBar(int actualBoss_, Texture* bar, Texture* life) : actualBoss((Boss)actualBoss_), barTx(bar), lifeTx(life) {}
	BossHealthBar(Entity* bossManager_, int actualBoss_, Texture* bar, Texture* life) : bossManager(bossManager_), actualBoss((Boss)actualBoss_), barTx(bar), lifeTx(life) {}
	void initComponent() override;
	void setBossLife(int n) { BossLife = n; }
	void damage(int n);
	void reset();
	void die();
	virtual void render();
private:
	bool isDead = false;
	Entity* bossManager = nullptr;
	Boss actualBoss;
	int maxWidth = 0;
	int BossLife = 0;
	int offset = 30;
	Texture* barTx;
	Texture* lifeTx;
	SDL_Rect posBar = {0, 0, 0, 0};
	SDL_Rect posLife = { 0, 0, 0, 0 };
};

