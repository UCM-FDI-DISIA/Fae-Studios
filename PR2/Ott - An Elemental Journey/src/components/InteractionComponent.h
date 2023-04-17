#pragma once
#include "LampAnimationComponent.h"
#include "Health.h"
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include <functional>

enum Interaction {LAMP_IT, SANCTUARY_IT, LIFESHARD_IT, GRASS_IT, ELEMENT_IT };

class InteractionComponent : public Component
{
public:
	InteractionComponent(std::function<void()> const& callback, Interaction type, int ID, int room, bool destroyAfterIntreaction = false) : callback(callback), 
		destroyAfterInteraction(destroyAfterIntreaction), type(type), intID(ID), room(room) {}
	//Para las lámparas de teletransporte
	virtual ~InteractionComponent() = default;
	void interact() { callback(); if (destroyAfterInteraction) { ent_->setAlive(false); } }
	void OnPlayerNear() {
		if (!nearPlayer) {
				switch (type) {
					case LAMP_IT:
						if (mngr_->getPlayer()->getComponent<Health>()->getElement() == ecs::Light) {
							ent_->getComponent<LampAnimationComponent>()->startOnwardsAnim();
						}
						ent_->getComponent<LampAnimationComponent>()->setNear(true);
						break;
					default:
						break;
				}
				nearPlayer = true;
		}
	};
	void OnPlayerLeave() {
		if (nearPlayer) {
			switch (type) {
				case LAMP_IT:
					if (mngr_->getPlayer()->getComponent<Health>()->getElement() == ecs::Light) {
						ent_->getComponent<LampAnimationComponent>()->startBackwardsAnim();
					}
					ent_->getComponent<LampAnimationComponent>()->setNear(false);
					break;
				default:
					break;
			}
			nearPlayer = false;
		}
	};
	constexpr static ecs::cmpId_type id = ecs::_INTERACTION;

	inline Interaction getType() { return type; }
	inline int getID() { return intID; }
	inline int getRoom() { return room; }
private:
	std::function<void()> callback;
	bool destroyAfterInteraction = false;
	Interaction type;
	int intID;
	int room;
	bool nearPlayer = false;
};