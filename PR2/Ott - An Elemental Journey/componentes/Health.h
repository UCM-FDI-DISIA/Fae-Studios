#pragma once
#include "Component.h"
#include "../Src/Manager.h"
class Health : public Component
{
private:
	int maxLife, actualLife;
	bool dead;
	ecs::elements elem;
	Entity* lastSanctuary = nullptr;
public:
	constexpr static cmpId_type id = ecs::_HEALTH;
	Health(int h, ecs::elements e) : Component(), maxLife(2*h), actualLife(2*h), elem(e), dead(false) {};
	//Este método activa la animación
	void die();
	//Este te lleva al santuario
	void recall();
	bool recieveDamage(ecs::elements elem);
	inline int getHealth() { return actualLife; }
	inline ecs::elements getElement() { return elem; }
	inline void setElement(int newElem) { 
		switch (newElem)
		{
		case 0: elem = ecs::Light; break;
		case 1: elem = ecs::Earth; break;
		case 2: elem = ecs::Water; break;
		case 3: elem = ecs::Fire; break;
		default: break;
		}
	}
	void saveSactuary();
};

