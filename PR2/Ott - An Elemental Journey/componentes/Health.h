#pragma once
#include "Component.h"
#include "../Src/Manager.h"
class Health : public Component
{
private:
	int maxLife, actualLife;
	ecs::elements elem;
	Entity* lastSanctuary = nullptr;
public:
	constexpr static cmpId_type id = ecs::_HEALTH;
	Health(int h, ecs::elements e) : Component(), maxLife(2*h), actualLife(2*h), elem(e) {};
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
		case 0: ecs::Light; break;
		case 1: ecs::Earth; break;
		case 2: ecs::Water; break;
		case 3: ecs::Fire; break;
		default: break;
		}
	}
	void saveSactuary();
};

