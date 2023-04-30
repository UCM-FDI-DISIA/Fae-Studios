#pragma once
#include "../ecs/Component.h"
#include "Transform.h"
#include "Health.h"
#include "../game/ecs.h"
class DamageArea: public Component
{
public:
	constexpr static ecs::cmpId_type id = ecs::_DAMAGE_AREA;
	DamageArea(ecs::elements el, bool lava) : element(el), lava(lava) {}
	virtual ~DamageArea() = default;
	virtual void update();
	virtual void initComponent();
private:
	Transform* tr;
	PhysicsComponent* pPhysics;
	Health* pHe;
	ecs::elements element;
	bool lava;
};

