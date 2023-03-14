#pragma once
#include "../ecs/Component.h"
#include "Transform.h"

class Destruction:public Component
{
private:
	Entity* boss;
	Transform* bossTransform;
	
	Transform* transform;

public:
	constexpr static ecs::cmpId_type id = ecs::_BOSS_DESTRUCTION;
	Destruction(Entity* ent) {
		boss = ent;
		bossTransform = boss->getComponent<Transform>();
	}
	~Destruction() {}
	void initComponent() override;
	void update() override;
};

