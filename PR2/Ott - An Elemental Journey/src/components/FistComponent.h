#pragma once
#include "../ecs/Entity.h"
#include "../ecs/Component.h"
#include "../components/Transform.h"
#include <list>

class FistComponent : public Component
{
public:
	FistComponent(int side, std::list<Entity*>::iterator it_, std::list<Entity*>* l_) {
		side_ = side; 
		if (side_ == 0)dir = { 3,0 };
		else dir = { 0,3 };
		it = it_;
		l = l_;
	};
	virtual ~FistComponent() { if(erase) l->erase(it); };
	void initComponent() override;
	void notErase() { erase = false; }
	constexpr static ecs::cmpId_type id = ecs::_FINALBOSS_ATTACK;
private:
	void update() override;
	bool erase = true;
	Transform* player;
	Transform* tr_;
	int initialXPos, initialYPos, maxDistance = 3000;
	int side_ = 0;
	Vector2D dir;
	std::list<Entity*>::iterator it;
	std::list<Entity*>* l;
};
