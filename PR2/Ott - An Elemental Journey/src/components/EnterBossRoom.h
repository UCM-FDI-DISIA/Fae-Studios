#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include "../ecs/Entity.h"
#include "Transform.h"
#include "../sdlutils/Texture.h"
#include "VineManager.h"
#include "PlayerInput.h"
#include "MapComponent.h"
#include "PhysicsComponent.h"
#include <string>

class EnterBossRoom : public Component
{
private:
	Entity* camera = nullptr;
	Entity* player = nullptr;
	Entity* earthBoss = nullptr;
	Entity* blockEnter = nullptr;
	Entity* blockExit = nullptr;
	SDL_Rect playerCollider;
	MapComponent* map = nullptr;
	int col = 0;
	bool start = false;
	bool added = false;
	bool startShaking = false;
	bool unlocked = false;
	SDL_Rect bossRoom;
	std::string roomNum = "13";
	bool hasEntered = false;

public:
	EnterBossRoom(SDL_Rect bR): bossRoom(bR) {}
	void initComponent();
	virtual ~EnterBossRoom() {}
	inline void StartShaking() {
		startShaking = true;
		timer = SDL_GetTicks();
		resetTime = true;
	}
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
