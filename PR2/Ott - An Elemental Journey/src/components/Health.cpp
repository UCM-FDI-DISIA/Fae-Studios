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
#include "FinalBossBehaviorComponent.h"
#include "ShieldComponent.h"
#include "AttackCharger.h"
#include "AutoDestroy.h"
#include "Image.h"
void Health::die()
{
	if (ent_->hasComponent<PlayerAnimationComponent>()) ent_->getComponent<PlayerAnimationComponent>()->setState(DIE);
	else if ((ent_->hasComponent<EnemyAnimationComponent>())) {
        ent_->getComponent<EnemyAnimationComponent>()->setState(DIE_ENEMY);
        mngr_->getPlayer()->getComponent<AttackCharger>()->addCharge(elementsInfo::ottMatrix[getElement()][mngr_->getPlayer()->getComponent<Health>()->getElement()] + 1);
    }
	else if ((ent_->hasComponent<FireBossAnimation>())) ent_->getComponent<FireBossAnimation>()->setState(DIE_FIREBOSS);
	else if (bar != nullptr &&(ent_->hasComponent<EarthBossAttack>()|| ent_->hasComponent<FinalBossBehaviorComponent>())) bar->die();
	else if(ent_->hasComponent<EnemyAnimationComponent>()) ent_->getComponent<EnemyAnimationComponent>()->setState(DIE_ENEMY);
	else ent_->setAlive(false);
	auto gen = ent_->getComponent<Generations>();
	// si la entidad muerta es un slime y no esta en su ultima gen manda a que se divida
	if (gen != nullptr && gen->getGeneration() > 1) ent_->getComponent<Generations>()->Divide();
	dead = true;
}

void Health::initComponent() {
	pAnim_ = ent_->getComponent<PlayerAnimationComponent>();
}

void Health::recall(bool rest) {
	Vector2D newPos;
	
	if (sanctuaryID != -1) {
		auto lastSanctuary = static_cast<PlayState*>(GameStateMachine::instance()->currentState())->getMap()->getSanctuary(sanctuaryID);
		if (lastSanctuary.sanct != nullptr && !rest) {
			auto sancTr_ = lastSanctuary.sanct->getComponent<Transform>();
			auto tr_ = ent_->getComponent<Transform>();
			newPos = sancTr_->getPosition() + Vector2D(0, sancTr_->getHeight() - tr_->getHeight());
			auto map = static_cast<PlayState*>(GameStateMachine::instance()->currentState())->getMap();
			if (lastSanctuary.mapKey != map->getCurrentLevel()) {
				if (lastSanctuary.mapKey == "earthMap") {
					map->changeMap(ecs::EARTH_MAP, lastSanctuary.mapKey);
				}
				else if (lastSanctuary.mapKey == "waterMap") {
					map->changeMap(ecs::WATER_MAP, lastSanctuary.mapKey);
				}
				else if (lastSanctuary.mapKey == "waterBossMap") {
					map->changeMap(ecs::WATER_BOSS_MAP, lastSanctuary.mapKey);
				}
				else if (lastSanctuary.mapKey == "fireMap") {
					map->changeMap(ecs::FIRE_MAP, lastSanctuary.mapKey);
				}
			}
			map->changeRoom(std::to_string(lastSanctuary.sanct->getComponent<InteractionComponent>()->getRoom()), newPos);
		}
	}
	else { 
		newPos = ent_->getComponent<Transform>()->getInitialPosition();
		static_cast<PlayState*>(GameStateMachine::instance()->currentState())->getMap()
			->changeRoom("0", newPos);
	}
	image->reset();
	actualLife = maxLife;
	static_cast<PlayState*>(GameStateMachine::instance()->currentState())->resetEnemies();
}

bool Health::recieveDamage(ecs::elements el, bool dir) {
	if (inmune) {
		/*auto inm = mngr_->addEntity(ecs::_grp_UI);
		auto tr = ent_->getComponent<Transform>();
		Vector2D middlePos = tr->getPosition() + Vector2D(tr->getHeight() / 2, tr->getWidth() / 2);
		inm->addComponent<Transform>(middlePos, tr->getWidth() * 0.3, tr->getWidth() * 0.3);
		switch (elem)
		{
		case ecs::Earth: inm->addComponent<Image>(&sdlutils().images().at("earthShield")); break;
		case ecs::Water: inm->addComponent<Image>(&sdlutils().images().at("waterShield")); break;
		case ecs::Fire: inm->addComponent<Image>(&sdlutils().images().at("fireShield")); break;
		default: inm->addComponent<Image>(&sdlutils().images().at("shield")); break;
		}
		inm->addComponent<AutoDestroy>(0.1);*/
		sdlutils().soundEffects().at("shield_block").play(0, ecs::_channel_PLAYER);
		return false;
	}
	if (ent_->hasComponent<PlayerAnimationComponent>()) {
		if (pAnim_->isInvincible()) return false;
		//si dir == true, knockback derecha
		ent_->getComponent<PhysicsComponent>()->knockback(dir);
		//if() A�adir da�o dependiendo de la entidad
		int damage = elementsInfo::ottMatrix[el][elem];

        switch (damage){
            case 2: sdlutils().soundEffects().at("hard_attack").play(0, ecs::_channel_PLAYER); break;
            case 1: sdlutils().soundEffects().at("hitTaken").play(0, ecs::_channel_PLAYER); break;
            case 0: sdlutils().soundEffects().at("soft_attack").play(0, ecs::_channel_PLAYER); break;
            case -1: sdlutils().soundEffects().at("useless_attack").play(0, ecs::_channel_PLAYER); break;
            default: sdlutils().soundEffects().at("hitTaken").play(0, ecs::_channel_PLAYER); break;
        }

		if (ent_->getComponent<ShieldComponent>()->hasShield()) damage = ent_->getComponent<ShieldComponent>()->checkDamage(damage, dir);
		if (damage != -1) {
			
			if (damage == 0) {
				if (image->setWeak()) damage = 1;
			}
			actualLife -= damage;
			image->damage(damage);
			pAnim_->playerDamaged();
		}
	}
	else if ((ent_->hasComponent<EarthBossAttack>() || ent_->hasComponent<FinalBossBehaviorComponent>()) && bar != nullptr) {
		int damage = elementsInfo::ottMatrix[el][elem];

        switch (damage){
            case 2: sdlutils().soundEffects().at("hard_attack").play(0, ecs::_channel_PLAYER); break;
            case 1: sdlutils().soundEffects().at("hitTaken").play(0, ecs::_channel_PLAYER); break;
            case 0: sdlutils().soundEffects().at("soft_attack").play(0, ecs::_channel_PLAYER); break;
            case -1: sdlutils().soundEffects().at("useless_attack").play(0, ecs::_channel_PLAYER); break;
            default: sdlutils().soundEffects().at("hitTaken").play(0, ecs::_channel_PLAYER); break;
        }

		actualLife -= (2*damage);
		bar->damage(damage);
	}
	else {
		if (!dead) {
            switch(ecs::matrix[el][elem]) {
                case 4:
                    sdlutils().soundEffects().at("hard_attack").play(0, ecs::_channel_PLAYER);
                    break;
                case 2:
                    sdlutils().soundEffects().at("hitTaken").play(0, ecs::_channel_PLAYER);
                    break;
                case 1:
                    sdlutils().soundEffects().at("soft_attack").play(0, ecs::_channel_PLAYER);
                    break;
                case 0:
                    sdlutils().soundEffects().at("useless_attack").play(0, ecs::_channel_PLAYER);
                    break;
                default:
                    sdlutils().soundEffects().at("hitTaken").play(0, ecs::_channel_PLAYER);
                    break;
            }
			actualLife -= ecs::matrix[el][elem];
			if(ent_->hasComponent<EnemyAnimationComponent>()) ent_->getComponent<EnemyAnimationComponent>()->damage(ecs::ottMatrix[el][elem]);
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

void Health::saveSactuary(Entity* sanct) {
	sanctuaryID = sanct->getComponent<InteractionComponent>()->getID();
	recall(true);
	// aqu� no estar�a mal poner una animaci�n de Ott sentaditto de pana
}

void Health::saveToFile(std::ofstream& file) {
	file << "sanctuaryID " << sanctuaryID << std::endl;
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