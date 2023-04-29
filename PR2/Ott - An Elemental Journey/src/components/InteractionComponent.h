#pragma once
#include "LampAnimationComponent.h"
#include "GrassAnimationComponent.h"
#include "Health.h"
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include <functional>
#include"../game/Game.h"

enum Interaction {LAMP_IT, SANCTUARY_IT, LIFESHARD_IT, GRASS_IT, ELEMENT_IT };

class InteractionComponent : public Component
{
public:
	InteractionComponent(std::function<void()> const& callback, Interaction type, int ID, int room, bool destroyAfterIntreaction = false) : callback(callback), 
		destroyAfterInteraction(destroyAfterIntreaction), type(type), intID(ID), room(room) {}
	//Para las lámparas de teletransporte
	virtual ~InteractionComponent() { 
		
	};
	inline void setIt(list<Entity*>::iterator i, list<Entity*>* v) { 
		listIt = i; 
		listPtr = v;
	}; 
	void interact() { callback(); if (destroyAfterInteraction) { ent_->setAlive(false); listPtr->erase(listIt); } }
	void OnPlayerNear() {
		if (!nearPlayer) {
			if (game().getIsJoystick() && SDL_JoystickHasRumble(game().getJoystick())) {
				SDL_JoystickRumble(game().getJoystick(), UINT16_MAX / 2, UINT16_MAX / 2, 1000);
			}
				switch (type) {
					case LAMP_IT:
						if (mngr_->getPlayer()->getComponent<Health>()->getElement() == ecs::Light) {
							ent_->getComponent<LampAnimationComponent>()->startOnwardsAnim();
						}
						ent_->getComponent<LampAnimationComponent>()->setNear(true);
						break;
					case GRASS_IT:
						ent_->getComponent<GrassAnimationComponent>()->startAnim();
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
				case GRASS_IT:
					ent_->getComponent<GrassAnimationComponent>()->stopAnim();
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
	list<Entity*>::iterator listIt;
	list<Entity*>* listPtr;
};