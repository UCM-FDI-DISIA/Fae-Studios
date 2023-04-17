#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include "../ecs/Entity.h"
#include "Transform.h"
#include "EnterBossRoom.h"

class Trigger : public Component
{
private:
	Entity* player_;
	Transform* tr_;
	bool detected = false;
public:
	Trigger();
	virtual ~Trigger() {}
	void initComponent() override;
	constexpr static ecs::cmpId_type id = ecs::_TRIGGER;
	void update() override;
};