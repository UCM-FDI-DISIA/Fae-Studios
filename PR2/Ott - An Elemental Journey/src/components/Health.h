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
	bool dead = false;
public:
	constexpr static ecs::cmpId_type id = ecs::_HEALTH;
	Health(int h, ecs::elements e, bool player = false) : Component(), elem(e) {
		if (player) { maxLife = h; actualLife = h; }
		else { maxLife = 2 * h; actualLife = 2 * h; }// La vida de los enemigos tiene una representación diferente
	};
	//Este método activa la animación
	void die();
	virtual void initComponent();
	//Este te lleva al santuario
	void recall();
	inline bool isDead() { return dead; }
	bool recieveDamage(ecs::elements el);
	inline int getHealth() { return actualLife; }
	inline int getMaxHealth() { return maxLife; }
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

