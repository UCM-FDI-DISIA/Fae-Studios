#pragma once
#include "../ecs/Component.h"
#include "Transform.h"
#include "MapComponent.h"

class Destruction:public Component
{
private:
	Entity* boss;
	Transform* bossTransform;
	
	Transform* transform;
	MapComponent* map;
	int index;
	std::string room;

public:
	constexpr static ecs::cmpId_type id = ecs::_BOSS_DESTRUCTION;
	Destruction(std::string room, int index, MapComponent* map, Entity* ent = nullptr) : room(room), index(index), map(map) {
		boss = ent;
		if(ent != nullptr) bossTransform = boss->getComponent<Transform>();
	}
	~Destruction() {}
	void setBoss(Entity* ent) { bossTransform = ent->getComponent<Transform>(); }
	void initComponent() override;
	void update() override;
};

