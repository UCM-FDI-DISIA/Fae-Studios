#pragma once
#include "../ecs/Entity.h"
#include "../ecs/Component.h"
#include "../components/Transform.h"
class FireWallComponent : public Component
{
public:
	FireWallComponent(Vector2D d);
	virtual ~FireWallComponent();
	void initComponent() override;
	constexpr static ecs::cmpId_type id = ecs::_FINALBOSS_ATTACK;
private:
	void update() override;
	Vector2D dir;
	Entity* player;
	Transform* tr_;
	int initialXPos, maxDistance = 900;
};
