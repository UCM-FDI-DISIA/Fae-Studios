#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include "../ecs/Entity.h"
#include "Transform.h"
#include "../sdlutils/Texture.h"
#include "VineManager.h"
#include "PlayerInput.h"
class EnterBossRoom : public Component
{
private:
	Entity* camera = nullptr;
	Entity* player = nullptr;
	Entity* earthBoss = nullptr;
	Entity* blockDoor = nullptr;
	Texture* anim = nullptr;
	int col = 0;
	bool start = false;
	bool added = false;

public:
	EnterBossRoom(Texture* a) : anim(a) {}
	void initComponent();
	virtual ~EnterBossRoom() {}
	constexpr static ecs::cmpId_type id = ecs::_ENTERBOSS;
	void enterRoom();
	void startFight();
	int timer = 2000;
	bool resetTime = true;
	void update() override;
	void startAnim() { start = true; }
};
