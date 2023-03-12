#pragma once
#include "Component.h"
#include "../dependencies/Vector2D.h"
#include "../Src/Entity.h"
#include "Transform.h"
#include "EnterBossRoom.h"

class Trigger: public Component
{
private:
	Entity* player_;
	Transform* tr_;
public:
	Trigger();
	virtual ~Trigger(){}
	void initComponent() override;
	constexpr static cmpId_type id = ecs::_TRIGGER;
	void update() override;
};

