#include "PlayerAttack.h"
#include "Transform.h"
#include "Health.h"
#include "../game/ecs.h"
#include "../ecs/Entity.h"
#include "PhysicsComponent.h"
#include "Image.h"
#include "Bullet.h"
#include "../sdlutils/SDLUtils.h"
#include "FramedImage.h" 

PlayerAttack::PlayerAttack(int width, int height) : tr_(nullptr), health_(nullptr), anim_(nullptr), physics(nullptr) {
	triggerHeight = height;
	triggerWidth = width;
	//triggerWH = Vector2D(width, height);
	canAttack = false;
	watAtackTriggWH = Vector2D(WATER_ATACK_WIDTH, WATER_ATACK_HEIGHT);
	waterAttackActive = false;
	earthAttackActive = false;
};

void PlayerAttack::initComponent() {
	tr_ = ent_->getComponent<Transform>();
	health_ = ent_->getComponent<Health>();
	anim_ = ent_->getComponent<PlayerAnimationComponent>();
	physics = ent_->getComponent<PhysicsComponent>();
}

void PlayerAttack::update() {

	//SDL_Rect trigger = { (int)triggerPos.getX(), (int)triggerPos.getY(), (int)watAtackTriggWH.getX(), (int)watAtackTriggWH.getY() };
	//MoveTrigger(watAtackTriggWH); // Se mueven los triggers a la posici�n actual

	if (anim_->getState() == ATTACK) { // ESTADO DE ATAQUE

		if (SDL_GetTicks() - startAttackingTime > AttackTime && canAttack) { // TIEMPO PARA HACER EL ATAQUE JUNTO CON LA ANIMACION
			switch (health_->getElement())
			{
			case ecs::Light: {
				MoveTrigger(Vector2D(triggerWidth, triggerHeight)); // Se mueven los triggers a la posici�n actual
				trigger = { (int)triggerPos.getX(), (int)triggerPos.getY(), triggerWidth, triggerHeight};
				attackEnemy(trigger);
				break;
			}
			case ecs::Earth: 
				MoveTrigger(watAtackTriggWH); // Se mueven los triggers a la posici�n actual
				trigger = { (int)triggerPos.getX(), (int)triggerPos.getY(), 0, triggerHeight }; //cambiar altura 
				if (!earthAttackActive)
				{
					tAttack = mngr_->addEntity(ecs::_grp_PROYECTILES);
					tAttack->addComponent<Transform>(Vector2D(trigger.x, trigger.y), EARTH_ATTACK_WIDTH, EARTH_ATTACK_HEIGHT);
					tAttack->addComponent<FramedImage>(&sdlutils().images().at("water_attack"));
					colEarthtrigger = 1;
					earthAttackActive = true;
					earthDurationTimer = SDL_GetTicks();
				}
				break;
			case ecs::Fire: {
				if (chargedAttack) { 
					remainingAttacks = 3; 
					lastFireBallTime = SDL_GetTicks() - timeBetweenFireBalls; 
					chargedAttack = false;
				}
				else spawnFireball();
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
					wAttack->addComponent<Image>(&sdlutils().images().at("water_attack"));

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
		wAttack->getComponent<Transform>()->setPosition(triggerPos);

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
	else if (earthAttackActive)
	{
		// Transform
		auto trAttack = tAttack->getComponent<Transform>();
		trAttack->setPosition(triggerPos);
		auto earthAnimation = tAttack->getComponent<FramedImage>();
		auto colAnim = earthAnimation->getCurrentCol();
		if (colEarthtrigger != colAnim + 1)
		{
			colEarthtrigger = colAnim + 1;
			trigger.w = colEarthtrigger * (trAttack->getWidth() / earthAnimation->getTexture()->getNumCols()) ;
		}
		//si CRECER -> atacckEnemy
		//bool attackEnemy, true->DECRECE
		attackEnemy(trigger);

		//setAlive false depende de la animación
	}
	if (remainingAttacks > 0 && SDL_GetTicks() - lastFireBallTime >= timeBetweenFireBalls) {
		spawnFireball();
		lastFireBallTime = SDL_GetTicks();
		--remainingAttacks;
	}
}

// PRIVATE


void PlayerAttack::spawnFireball()
{
	//MoveTrigger(triggerWH); // Se mueven los triggers a la posici�n actual
	auto pTransf = ent_->getComponent<Transform>();
	Entity* attack = mngr_->addEntity(ecs::_grp_PROYECTILES);
	Vector2D shootPos = Vector2D(pTransf->getPosition().getX(), pTransf->getPosition().getY() + pTransf->getHeight() / 2);
	if (ent_->getComponent<PhysicsComponent>()->getLookDirection()) attack->addComponent<PhysicsComponent>(Vector2D(1, 0));
	else attack->addComponent<PhysicsComponent>(Vector2D(-1, 0));
	attack->addComponent<Transform>(shootPos, 50, 50);
	attack->addComponent<Image>(&sdlutils().images().at("ott_luz"));
	attack->addComponent<Bullet>(health_->getElement(), ent_);
}

void PlayerAttack::MoveTrigger(Vector2D attackWH) {
	int playerW = tr_->getWidth();
	int playerH = tr_->getHeight();
	Vector2D playerPos = tr_->getPosition();

	if (physics->getLookDirection()) {
		triggerPos = Vector2D(playerPos.getX() + playerW, playerPos.getY() + playerW / 2);
	}
	else {
		triggerPos = Vector2D(playerPos.getX() - attackWH.getX(), playerPos.getY() + playerW / 2);
	}
}

// Ataca enemigo si esta en la zona de ataque
void PlayerAttack::attackEnemy(SDL_Rect& attackZone) {
	auto enemiesGrp = mngr_->getEntities(ecs::_grp_CHARACTERS);

	for (auto e : enemiesGrp) {

		SDL_Rect rect = e->getComponent<Transform>()->getRect();

		// Si enemigo y ataque interseccionan
		if (SDL_HasIntersection(&rect, &attackZone)) {

			// Hace da�o a enemigo dependiendo del elemento
			e->getComponent<Health>()->recieveDamage(health_->getElement());
		}
	}
}

