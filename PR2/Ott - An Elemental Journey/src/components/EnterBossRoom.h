#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include "../ecs/Entity.h"
#include "Transform.h"
#include "../sdlutils/Texture.h"
#include "VineManager.h"
#include "PlayerInput.h"
#include "MapComponent.h"

class EnterBossRoom : public Component
{
private:
	Entity* camera = nullptr;
	Entity* player = nullptr;
	Entity* earthBoss = nullptr;
	Entity* blockEnter = nullptr;
	Entity* blockExit = nullptr;
	MapComponent* map;
	int col = 0;
	bool start = false;
	bool added = false;
	bool startShaking = false;
	bool unlocked = false;
	SDL_Rect bossRoom;

public:
	EnterBossRoom(SDL_Rect bR): bossRoom(bR) {}
	void initComponent();
	virtual ~EnterBossRoom() {}
	constexpr static ecs::cmpId_type id = ecs::_ENTERBOSS;
	void enterRoom();
	void blockDoors();
	void unlockDoors();
	void startFight();
	int timer = 2000;
	bool resetTime = true;
	void update() override;
	void startAnim() { start = true; }
};
