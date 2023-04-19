#pragma once
#include "../ecs/Entity.h"
#include "../ecs/Component.h"
#include "../components/Transform.h"
class FistComponent : public Component
{
public:
	FistComponent(Vector2D d);
	virtual ~FistComponent();
	void initComponent() override;
	constexpr static ecs::cmpId_type id = ecs::_FINALBOSS_ATTACK;
private:
	void update() override;
	Vector2D dir;
	Entity* player;
	Transform* tr_;
	int initialXPos, maxDistance = 900;
};
