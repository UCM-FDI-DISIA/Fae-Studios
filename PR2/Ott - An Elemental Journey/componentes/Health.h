#pragma once
#include "Component.h"
#include "HealthImage.h"
#include "../Src/Manager.h"

class Health : public Component
{
private:
	int maxLife, actualLife;
	bool dead;
	ecs::elements elem;
	Entity* lastSanctuary = nullptr;
	HealthImage* image;
	PlayerAnimationComponent* pAnim_;
public:
	constexpr static cmpId_type id = ecs::_HEALTH;
	Health(int h, ecs::elements e, bool player = true) : Component(), elem(e), dead(false) { if (player) { maxLife = h; actualLife = h; } else { maxLife = 2 * h; actualLife = 2 * h; } };
	//Este método activa la animación
	void die();
	virtual void initComponent();
	//Este te lleva al santuario
	void recall();
	bool recieveDamage(ecs::elements elem);
	inline int getMaxHealth() { return maxLife; }
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
	bool isDead() { return dead; };
};

