#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include <functional>

enum Interaction {LAMP_IT, SANCTUARY_IT, LIFESHARD_IT, GRASS_IT };

class InteractionComponent : public Component
{
public:
	InteractionComponent(std::function<void()> const& callback, Interaction type, int ID, bool destroyAfterIntreaction = false) : callback(callback), destroyAfterInteraction(destroyAfterIntreaction), type(type), intID(ID) {}
	//Para las lámparas de teletransporte
	virtual ~InteractionComponent() = default;
	void interact() { callback(); if (destroyAfterInteraction) { ent_->setAlive(false); } }

	constexpr static ecs::cmpId_type id = ecs::_INTERACTION;

	inline Interaction getType() { return type; }
	inline int getID() { return intID; }
private:
	
	std::function<void()> callback;
	bool destroyAfterInteraction = false;
	Interaction type;
	int intID;
};
