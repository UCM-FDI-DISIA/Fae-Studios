#include "Health.h"
#include "../ecs/Entity.h"
#include "Transform.h"
#include "PlayerAnimationComponent.h"
#include "EnemyAnimationController.h"
#include "FireBossAnimation.h"
#include "Generations.h"
#include "../game/Elements.h"
#include "../states/PlayState.h"
#include "../states/GameStateMachine.h"
#include "EarthBossManager.h"
#include "EarthBossAttack.h"
#include "InteractionComponent.h"
#include "ShieldComponent.h"
#include "AttackCharger.h"

void Health::die()
{
	if (ent_->hasComponent<PlayerAnimationComponent>()) ent_->getComponent<PlayerAnimationComponent>()->setState(DIE);
	else if ((ent_->hasComponent<EnemyAnimationComponent>())) {
        ent_->getComponent<EnemyAnimationComponent>()->setState(DIE_ENEMY);
        mngr_->getPlayer()->getComponent<AttackCharger>()->addCharge(elementsInfo::ottMatrix[getElement()][mngr_->getPlayer()->getComponent<Health>()->getElement()] + 1);
    }
	else if ((ent_->hasComponent<FireBossAnimation>())) ent_->getComponent<FireBossAnimation>()->setState(DIE_FIREBOSS);
	else if (bar != nullptr && ent_->hasComponent<EarthBossAttack>()) bar->die();
	else if(ent_->hasComponent<EnemyAnimationComponent>()) ent_->getComponent<EnemyAnimationComponent>()->setState(DIE_ENEMY);
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

void Health::recall(bool rest)
{
	Vector2D newPos;
	if (lastSanctuary != nullptr && !rest) {
		auto sancTr_ = lastSanctuary->getComponent<Transform>();
		auto tr_ = ent_->getComponent<Transform>();
		newPos = sancTr_->getPosition() + Vector2D(0, sancTr_->getHeight() - tr_->getHeight());
		static_cast<PlayState*>(GameStateMachine::instance()->currentState())->getMap()
			->changeRoom(std::to_string(lastSanctuary->getComponent<InteractionComponent>()->getRoom()), newPos);
	}
	else 
	{ 
		newPos = ent_->getComponent<Transform>()->getInitialPosition();
		static_cast<PlayState*>(GameStateMachine::instance()->currentState())->getMap()
			->changeRoom("0", newPos);
	}
	image->reset();
	actualLife = maxLife;
	static_cast<PlayState*>(GameStateMachine::instance()->currentState())->resetEnemies();
}

bool Health::recieveDamage(ecs::elements el, bool dir)
{
	if (ent_->hasComponent<PlayerAnimationComponent>()) {
		if (pAnim_->isInvincible()) return false;
		pAnim_->playerDamaged();
		//si dir == true, knockback derecha
		ent_->getComponent<PhysicsComponent>()->knockback(dir);
		//if() A�adir da�o dependiendo de la entidad
		int damage = elementsInfo::ottMatrix[el][elem];

		if (ent_->getComponent<ShieldComponent>()->hasShield()) damage = ent_->getComponent<ShieldComponent>()->checkDamage(damage, dir);
		if (damage != -1) {
			actualLife -= damage;
			if (damage == 0) {
				if (image->setWeak()) damage = 1;
			}
			image->damage(damage);
		}
	}
	else if (ent_->hasComponent<EarthBossAttack>() && bar != nullptr) {
		int damage = elementsInfo::ottMatrix[el][elem];
		actualLife -= (2*damage);
		bar->damage(damage);
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

void Health::saveSactuary(Entity* sanct)
{
	lastSanctuary = sanct;
	sanctuaryID = lastSanctuary->getComponent<InteractionComponent>()->getID();
	recall(true);
	// aqu� no estar�a mal poner una animaci�n de Ott sentaditto de pana
}

void Health::saveToFile(std::ofstream& file) {
	file << "sanctuaryID " << lastSanctuary->getComponent<InteractionComponent>()->getID() << std::endl;
	file << "lifeShards " << numShards << lifeShardIDs << "_" << std::endl;
}

void Health::loadFromFile(std::ifstream& file) {
	std::string aux;
	std::string aux2;
	file >> aux >> sanctuaryID >> aux >> numShards;
	file >> aux2;
	while (aux2 != "_") {
		lifeShardIDs += aux2 + " ";
		file >> aux2;
	}
	int shards = numShards;
	for (shards; shards > 1; shards -= 2) {
		increaseMaxLife();
	}
}