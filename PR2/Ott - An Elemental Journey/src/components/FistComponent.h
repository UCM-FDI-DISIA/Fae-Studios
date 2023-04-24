#pragma once
#include "../ecs/Entity.h"
#include "../ecs/Component.h"
#include "../components/Transform.h"
class FistComponent : public Component
{
public:
	FistComponent() {};
	virtual ~FistComponent();
	void initComponent() override;
	constexpr static ecs::cmpId_type id = ecs::_FINALBOSS_ATTACK;
private:
	void update() override;
	Entity* player;
	Transform* tr_;
	int initialXPos, maxDistance = 900;
};
