#include "EarthBossAttack.h"
#include "Health.h"
#include "../sdlutils/RandomNumberGenerator.h"
#include"../ecs/Entity.h"
#include "../ecs/Manager.h"

void EarthBossAttack::initComponent() {
	player = mngr_->getPlayer();
	playerCollider_ = player->getComponent<PhysicsComponent>();
	tr_ = ent_->getComponent<Transform>();
}

void EarthBossAttack::attack() {
	auto playerHealth = player->getComponent<Health>();
	if (playerHealth->getHealth() > 0) {
		playerHealth->recieveDamage(ecs::Earth, true);
		//playerHealth->recieveDamage(playerHealth->getElement(), true);
	}
}

void EarthBossAttack::update() {
	auto pCollider = playerCollider_->getCollider();
	if (SDL_HasIntersection(&pCollider, &tr_->getRect())) {
		attack();
	}
}