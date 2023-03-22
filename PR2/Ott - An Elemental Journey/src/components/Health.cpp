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
	else if ((ent_->hasComponent<EnemyAnimationComponent>())) ent_->getComponent<EnemyAnimationComponent>()->setState(DIE_ENEMY);
	else ent_->setAlive(false);
	auto gen = ent_->getComponent<Generations>();
	// si la entidad muerta es un slime y no esta en su ultima gen manda a que se divida
	if (gen != nullptr && gen->getGeneration() > 1) ent_->getComponent<Generations>()->Divide();
	dead = true;
}

void Health::initComponent() {
	pAnim_ = ent_->getComponent<PlayerAnimationComponent>();
	image = ent_->getComponent<HealthImage>();
}

void Health::recall()
{
	if (lastSanctuary != nullptr) {
		Vector2D newPos = lastSanctuary->getComponent<Transform>()->getPosition();
		image->reset();
		ent_->getComponent<Transform>()->setPosition(newPos);
		actualLife = maxLife;
		dead = false;
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
			if(ent_->hasComponent<EnemyAnimationComponent>()) ent_->getComponent<EnemyAnimationComponent>()->damage();
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

void Health::saveSactuary()
{
	lastSanctuary = static_cast<PlayState*>(GameStateMachine::instance()->getPlayState())->getCurrentInteraction();
	// die();
}
