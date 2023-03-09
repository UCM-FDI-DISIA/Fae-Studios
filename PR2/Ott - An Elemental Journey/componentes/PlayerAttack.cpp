#include "PlayerAttack.h"
#include "Transform.h"
#include "PlayerAnimationComponent.h"
#include "Health.h"
#include "../Src/ecs.h"
PlayerAttack::PlayerAttack(int width, int height) : tr_(nullptr), health_(nullptr), anim_(nullptr), physics(nullptr) { 
	triggerWH = Vector2D(width, height); 
	canAttack = false;
};

void PlayerAttack::initComponent() {
	tr_ = ent_->getComponent<Transform>();
	health_ = ent_->getComponent<Health>();
	anim_ = ent_->getComponent<PlayerAnimationComponent>();
	physics = ent_->getComponent<PhysicsComponent>();
}

void PlayerAttack::startAttack() {
	startAttackingTime = SDL_GetTicks();
	canAttack = true;
}

void PlayerAttack::update() {
	MoveTrigger(); // Se mueven los triggers a la posición actual
	if (anim_->getState() == ATTACK) { // ESTADO DE ATAQUE
		if (SDL_GetTicks() - startAttackingTime > AttackTime && canAttack) { // TIEMPO PARA HACER EL ATAQUE JUNTO CON LA ANIMACION
			SDL_Rect trigger;
			switch (health_->getElement())
			{
			case ecs::Light: {
				trigger = {(int)triggerPos.getX(), (int)triggerPos.getY(), (int)triggerWH.getX(), (int)triggerWH.getY() };
				auto enemiesGrp = mngr_->getEntitiesByGroup(ecs::_grp_CHARACTERS);
				for (auto e : enemiesGrp) {
					SDL_Rect rect = e->getComponent<Transform>()->getRect();
					if (SDL_HasIntersection(&rect, &trigger)) {
						e->getComponent<Health>()->recieveDamage(health_->getElement());
					}
				}
				break;
			}
			case ecs::Earth: break;
			case ecs::Fire: {
				auto pTransf = ent_->getComponent<Transform>();
				Entity* attack = mngr_->addEntity(ecs::_grp_PROYECTILES);
				Vector2D shootPos = Vector2D(pTransf->getPos().getX(), pTransf->getPos().getY() + pTransf->getH() / 2);
				attack->addComponent<Transform>(shootPos, 50,50);
				attack->addComponent<PhysicsComponent>(Vector2D(1,0));
				attack->addComponent<Image>(mngr_->getTexture(4));
				attack->addComponent<Bullet>(health_->getElement(), ent_);
				break;
			}
			case ecs::Water: break;
			default:
				break;
			}
			
			canAttack = false;
		}
	}
}

void PlayerAttack::MoveTrigger() {
	if (physics->getLookDirection()) {
		triggerPos = Vector2D(tr_->getPos().getX() + tr_->getW(), tr_->getPos().getY());
	}
	else {
		triggerPos = Vector2D(tr_->getPos().getX() - triggerWH.getX(), tr_->getPos().getY());
	}
}
