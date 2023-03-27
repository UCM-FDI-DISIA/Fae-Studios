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
#include "BossDoor.h"
class PlayerInput : public Component {
public:
	PlayerInput();
	virtual ~PlayerInput();
	virtual void initComponent();
	virtual void update();

	virtual void saveToFile(std::ofstream& file);
	virtual void loadFromFile(std::ifstream& file);
	constexpr static ecs::cmpId_type id = ecs::_CTRL;
	
	inline void unlockElement(ecs::elements elem) {
		switch (elem)
		{
		case ecs::Earth:
			earth = true;
			bossDoor->unlockElem(ecs::Earth);
			break;
		case ecs::Water:
			water = true;
			bossDoor->unlockElem(ecs::Water);
			break;
		case ecs::Fire:
			fire = true;
			bossDoor->unlockElem(ecs::Fire);
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
	inline void getDoor(Entity* door)
	{
		bossDoor = door->getComponent<BossDoor>();
	}

private:
	Transform* tr_;
	PhysicsComponent* physics_;
	PlayerAnimationComponent* anim_;
	PlayerAttack* attack_;
	FramedImageOtt* image_;
	Health* health_;
	BossDoor* bossDoor=nullptr;
	float horizontalSpeed = 0;
	int attackTimer, chargedAttackTime = 1;
	bool attack = false;
	bool earth = false, water = false, fire = false;
	bool selectedEarth = false, selectedWater = false, selectedFire = false, selectedLight = true;
	bool openingMap = false;
};



