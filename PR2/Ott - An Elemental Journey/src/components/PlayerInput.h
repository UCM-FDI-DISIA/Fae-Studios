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
#include "ShieldComponent.h"

class PlayerInput : public Component {
public:
	PlayerInput();
	virtual ~PlayerInput();
	virtual void initComponent();
	virtual void update();

	virtual void saveToFile(std::ofstream& file);
	virtual void loadFromFile(std::ifstream& file);
	constexpr static ecs::cmpId_type id = ecs::_CTRL;
	inline void setCanInteract(bool value) { canInteract = value; }
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
	inline bool hasElement(ecs::elements elem) {
		switch (elem)
		{
		case ecs::Earth:
			return earth;
			break;
		case ecs::Water:
			return water;
			break;
		case ecs::Fire:
			return fire;
			break;
		default:
			break;
		}
	}
	inline void stunStart() {
		stunned = true; timerStunned = SDL_GetTicks();
	}
private:
	Transform* tr_;
	PhysicsComponent* physics_;
	PlayerAnimationComponent* anim_;
	PlayerAttack* attack_;
	FramedImageOtt* image_;
	Health* health_;
	ShieldComponent* shield_;

	float horizontalSpeed = 0;
	int attackTimer, chargedAttackTime = 1;
	bool attack = false;
	bool earth = false, water = true, fire = false;
	bool selectedEarth = false, selectedWater = false, selectedFire = false, selectedLight = true;
	bool openingMap = false;
	bool canInteract = false;
	bool stunned = false;
	int stunnedTime = 2, timerStunned;
};



