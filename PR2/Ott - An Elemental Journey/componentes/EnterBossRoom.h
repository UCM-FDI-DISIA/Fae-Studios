#pragma once
#include "Component.h"
#include "../dependencies/Vector2D.h"
#include "../Src/Entity.h"
#include "Transform.h"
#include "../dependencies/Texture.h"
#include "VineManager.h"
#include "../dependencies/Texture.h"
class EnterBossRoom : public Component
{
private:
	Entity* camera = nullptr;
	Entity* player = nullptr;
	Entity* blockDoor = nullptr;
	Texture* anim = nullptr;
	int col = 0;
	bool start = false;

public:
	EnterBossRoom(Texture* a): anim(a) {}
	virtual ~EnterBossRoom(){}
	constexpr static cmpId_type id = ecs::_ENTERBOSS;
	void enterRoom();
	int timer = 2000;
	bool resetTime = true;
	void update() override;
	void initComponent() override;
	void startAnim() { start = true; }
};

