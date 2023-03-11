//LIMPIO -> A FALTA DE CAMBIAR EL MANAGER

#pragma once
#include "PhysicsComponent.h"
class Bullet : public Component {
private:
	Entity* player;
	ecs::elements elem;
	PhysicsComponent* physics;

public:
	constexpr static ecs::cmpId_type id = ecs::_BULLET;
	
	Bullet(ecs::elements e) : Component(), player(nullptr), elem(e), physics(nullptr) {};
	
	void initComponent() override;
	void update() override;
};

