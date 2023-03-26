#pragma once
#include "../ecs/Component.h"
#include "../sdlutils/InputHandler.h"
#include <iostream>
#include "Transform.h"
#include "PhysicsComponent.h"
#include "PlayerAnimationComponent.h"
#include "../ecs/Entity.h"
#include "Health.h"
#include "FramedImage.h"
#include "PlayerAttack.h"
#include "AttackCharger.h"

class PlayerInput : public Component {
public:
	PlayerInput();
	virtual ~PlayerInput();
	virtual void initComponent();
	virtual void update();
	constexpr static ecs::cmpId_type id = ecs::_CTRL;
	inline void unlockElement(ecs::elements elem) {
		switch (elem)
		{
		case ecs::Earth:
			earth = true;
			selectedEarth = true;
			selectedWater = false;
			selectedFire = false;
			selectedLight = false;
			break;
		case ecs::Water:
			water = true;
			selectedEarth = false;
			selectedWater = true;
			selectedFire = false;
			selectedLight = false;
			break;
		case ecs::Fire:
			fire = true;
			selectedEarth = false;
			selectedWater = false;
			selectedFire = true;
			selectedLight = false;
			break;
		default:
			break;
		}
		sdlutils().soundEffects().at("pick_elem").play(0, ecs::_channel_ALERTS);
	};

private:
	Transform* tr_;
	PhysicsComponent* physics_;
	PlayerAnimationComponent* anim_;
	PlayerAttack* attack_;
	FramedImageOtt* image_;
	Health* health_;
	float horizontalSpeed = 0;
	int attackTimer, chargedAttackTime = 1;
	bool attack = false;
	bool earth = false, water = false, fire = false;
	bool selectedEarth = false, selectedWater = false, selectedFire = false, selectedLight = true;
	bool openingMap = false;
};



