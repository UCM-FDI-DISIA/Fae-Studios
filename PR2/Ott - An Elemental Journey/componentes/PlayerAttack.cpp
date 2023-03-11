#include "PlayerAttack.h"
#include "Transform.h"

#include "../SDLApplication.h"
#include "Health.h"
#include "../Src/ecs.h"
PlayerAttack::PlayerAttack(SDLApplication* sdlAplication, int width, int height) : tr_(nullptr), health_(nullptr), anim_(nullptr), physics(nullptr) {
	triggerWH = Vector2D(width, height);
	canAttack = false;
	watAtackTriggWH = Vector2D(WATER_ATACK_WIDTH, WATER_ATACK_HEIGHT);
	waterAttackActive = false;
	game = sdlAplication;
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

	SDL_Rect trigger = { (int)triggerPos.getX(), (int)triggerPos.getY(), (int)watAtackTriggWH.getX(), (int)watAtackTriggWH.getY() };
	MoveTrigger(watAtackTriggWH); // Se mueven los triggers a la posici�n actual

	if (anim_->getState() == ATTACK) { // ESTADO DE ATAQUE

		if (SDL_GetTicks() - startAttackingTime > AttackTime && canAttack) { // TIEMPO PARA HACER EL ATAQUE JUNTO CON LA ANIMACION
			switch (health_->getElement())
			{
			case ecs::Light: {
				MoveTrigger(triggerWH); // Se mueven los triggers a la posici�n actual
				trigger = { (int)triggerPos.getX(), (int)triggerPos.getY(), (int)triggerWH.getX(), (int)triggerWH.getY() };
				attackEnemy(trigger);
				break;
			}
			case ecs::Earth: break;
			case ecs::Fire: {
				MoveTrigger(triggerWH); // Se mueven los triggers a la posici�n actual
				auto pTransf = ent_->getComponent<Transform>();
				Entity* attack = mngr_->addEntity(ecs::_grp_PROYECTILES);
				Vector2D shootPos = Vector2D(pTransf->getPos().getX(), pTransf->getPos().getY() + pTransf->getH() / 2);
				attack->addComponent<Transform>(shootPos, 50, 50);
				if (ent_->getComponent<PhysicsComponent>()->getLookDirection()) attack->addComponent<PhysicsComponent>(Vector2D(1, 0));
				else attack->addComponent<PhysicsComponent>(Vector2D(-1, 0));
				attack->addComponent<Image>(mngr_->getTexture(4));
				attack->addComponent<Bullet>(health_->getElement(), ent_);
				break;
			}
			case ecs::Water: {
				MoveTrigger(watAtackTriggWH); // Se mueven los triggers a la posici�n actual

				// Trigger de ataque
				trigger = { (int)triggerPos.getX(), (int)triggerPos.getY(), (int)watAtackTriggWH.getX(), (int)watAtackTriggWH.getY() };

				// Si no hay ya uno activo
				if (!waterAttackActive) {

					// Añado entidad de ataque
					wAttack = mngr_->addEntity(ecs::_grp_PROYECTILES);

					// Entidad ataque
					wAttack->addComponent<Transform>(Vector2D(trigger.x, trigger.y), trigger.w, trigger.h);
					wAttack->addComponent<Image>(game->getTexture("waterAttack", PLAY_STATE));

					waterAttackActive = true;
					waterDurationTimer = SDL_GetTicks();
				}

				break;
			}
			default: {
				break;
			}
			}

			canAttack = false;
		}
	}


	if (waterAttackActive) {

		// Transform
		wAttack->getComponent<Transform>()->setPos(triggerPos);

		// Si han pasado los segundos totales de la duracio, mata el ataque
		if (SDL_GetTicks() >= waterDurationTimer + WATER_ATACK_DURATION) {
			waterAttackActive = false;
			wAttack->setAlive(false);
		}

		// Si ha pasado el tiempo del tick, hace da�o
		if (SDL_GetTicks() >= waterTickTimer) {

			// Ataca enemigo
			attackEnemy(trigger);
			waterTickTimer = SDL_GetTicks() + WATER_ATACK_TICK_TIME;
		}
	}

}

// PRIVATE

void PlayerAttack::MoveTrigger(Vector2D attackWH) {
	int playerW = tr_->getW();
	int playerH = tr_->getH();
	Vector2D playerPos = tr_->getPos();

	if (physics->getLookDirection()) {
		triggerPos = Vector2D(playerPos.getX() + playerW, playerPos.getY() + playerW / 2);
	}
	else {
		triggerPos = Vector2D(playerPos.getX() - attackWH.getX(), playerPos.getY() + playerW / 2);
	}
}

// Ataca enemigo si esta en la zona de ataque
void PlayerAttack::attackEnemy(SDL_Rect& attackZone) {
	auto enemiesGrp = mngr_->getEntitiesByGroup(ecs::_grp_CHARACTERS);

	for (auto e : enemiesGrp) {

		SDL_Rect rect = e->getComponent<Transform>()->getRect();

		// Si enemigo y ataque interseccionan
		if (SDL_HasIntersection(&rect, &attackZone)) {

			// Hace da�o a enemigo dependiendo del elemento
			e->getComponent<Health>()->recieveDamage(health_->getElement());
		}
	}
}