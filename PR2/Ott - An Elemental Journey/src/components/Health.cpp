#include "Health.h"
#include "../ecs/Entity.h"
#include "Transform.h"
#include "PlayerAnimationComponent.h"
#include "EnemyAnimationController.h"
#include "Generations.h"
#include "../game/Elements.h"
#include "../states/PlayState.h"
#include "../states/GameStateMachine.h"

void Health::die()
{
	if (ent_->hasComponent<PlayerAnimationComponent>()) ent_->getComponent<PlayerAnimationComponent>()->setState(DIE);
	else ent_->getComponent<EnemyAnimationComponent>()->setState(DIE_ENEMY);
	auto gen = ent_->getComponent<Generations>();
	// si la entidad muerta es un slime y no esta en su ultima gen manda a que se divida
	if (gen != nullptr && gen->getGeneration() > 1) ent_->getComponent<Generations>()->Divide();
	dead = true;
}

void Health::initComponent() {
	pAnim_ = ent_->getComponent<PlayerAnimationComponent>();
	image = ent_->getComponent<HealthImage>();
}

void Health::recall(bool rest)
{
	if (lastSanctuary != nullptr) {
		auto sancTr_ = lastSanctuary->getComponent<Transform>();
		auto tr_ = ent_->getComponent<Transform>();
		image->reset();
		if (!rest) {
			Vector2D newPos = sancTr_->getPosition() + Vector2D(0, sancTr_->getHeight() - tr_->getHeight());
			tr_->setPosition(newPos);
		}
		actualLife = maxLife;
		dead = false;
		static_cast<PlayState*>(GameStateMachine::instance()->currentState())->resetEnemies();
		std::cout << "vuelvo a santuario" << std::endl;
	}
	else 
	{ 
		std::cout << "me muero para siempre" << std::endl; 
		Vector2D newPos = ent_->getComponent<Transform>()->getInitialPosition();
		image->reset();
		ent_->getComponent<Transform>()->setPosition(newPos);
		actualLife = maxLife;
		dead = false;

	}
}

bool Health::recieveDamage(ecs::elements el)
{
	if (ent_->hasComponent<PlayerAnimationComponent>()) {
		if (pAnim_->isInvincible()) return false;
		pAnim_->playerDamaged();
		ent_->getComponent<PhysicsComponent>()->knockback();
		//if() Añadir daño dependiendo de la entidad
		int damage = elementsInfo::ottMatrix[el][elem];
		actualLife -= damage;
		if (damage == 0) {
			if (image->setWeak()) damage = 1;
		}
		image->damage(damage);
	}
	else {
		if (!dead) {
			actualLife -= ecs::matrix[el][elem];
			ent_->getComponent<EnemyAnimationComponent>()->damage();
		}
	}
	std::cout << "LIFE (HEALTH): " << actualLife << std::endl;
	//startDamagedTime = SDL_GetTicks();
	if (!dead && actualLife <= 0) {
		die();
		return true;
	}
	else return false;
}

void Health::saveSactuary(Entity* sanct)
{
	lastSanctuary = sanct;
	recall(true);
	// aquí no estaría mal poner una animación de Ott sentaditto de pana
}
