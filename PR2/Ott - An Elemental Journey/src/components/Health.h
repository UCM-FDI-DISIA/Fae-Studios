#pragma once
#include "../ecs/Component.h"
#include "../ecs/Manager.h"
#include "HealthImage.h"
#include "PlayerAnimationComponent.h"

class Health : public Component
{
private:
	int maxLife, actualLife;
	ecs::elements elem;
	Entity* lastSanctuary = nullptr;
	HealthImage* image;
	PlayerAnimationComponent* pAnim_;
public:
	constexpr static ecs::cmpId_type id = ecs::_HEALTH;
	Health(int h, ecs::elements e) : Component(), maxLife(2 * h), actualLife(2 * h), elem(e) {};
	//Este método activa la animación
	void die();
	virtual void initComponent();
	//Este te lleva al santuario
	void recall();
	bool recieveDamage(ecs::elements el);
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

