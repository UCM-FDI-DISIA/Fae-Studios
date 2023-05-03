#pragma once
#include "../ecs/Component.h"
#include "Transform.h"
#include "Health.h"
#include "../game/ecs.h"
#include "FinalBossBehaviorComponent.h"
class DamageArea : public Component
{
public:
	constexpr static ecs::cmpId_type id = ecs::_DAMAGE_AREA;
	DamageArea(ecs::elements el, bool lava, FinalBossBehaviorComponent* bossBehaComp = nullptr) : element(el), lava(lava) 
	{
		if (bossBehaComp != nullptr)
		{
			bossBehaComp_ = bossBehaComp;
		}
	}
	virtual ~DamageArea() = default;
	virtual void update();
	virtual void initComponent();
private:
	Transform* tr;
	PhysicsComponent* pPhysics;
	Health* pHe;
	FinalBossBehaviorComponent* bossBehaComp_;
	ecs::elements element;
	bool lava;
	int lifeTime = 10000,
		spawnTime;

};