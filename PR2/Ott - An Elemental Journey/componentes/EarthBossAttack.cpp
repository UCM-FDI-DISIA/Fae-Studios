#include "EarthBossAttack.h"
#include "Health.h"
#include "../sdlutils/RandomNumberGenerator.h"
#include "../Src/Entity.h"
#include "../Src/Manager.h"

void EarthBossAttack::chooseRandomPos() {
	RandomNumberGenerator a;
	int aux = a.nextInt(1, 6);
	tr_->setPos(Vector2D(X_Positions[aux], BossZone_.y - 20));
}

void EarthBossAttack::initComponent() {
	player = mngr_->getPlayer();
	playerTr_ = player->getComponent<Transform>();
	tr_ = ent_->getComponent<Transform>();
	eAttack_ = ent_->getComponent<EnemyAttack>();
	waitingTime = SDL_GetTicks();
	chooseRandomPos();
}

void EarthBossAttack::attack() {
	auto playerHealth = player->getComponent<Health>();
	if (playerHealth->getHealth() > 0) {
		playerHealth->recieveDamage(playerHealth->getElement());
	}
}

// si detecta al jugador en alguna zona de la sala se mueve allí 
void EarthBossAttack::update() {
	if (tr_->getPos().getY() >= BossZone_.y + BossZone_.h) {
		attacking = false;
	}
	if (SDL_HasIntersection(&playerTr_->getRect(), &tr_->getRect())) {
		attack();
	}
	if (attacking) {
		tr_->setPos(Vector2D(tr_->getPos().getX(), tr_->getPos().getY() + 1)); 
	}
	else if (canAttack) {
		if (SDL_GetTicks() - waitingTime >= 5000) {
			int i = 0;
			while (!SDL_HasIntersection(&playerTr_->getRect(), &zones[i])) i++;
			tr_->setPos(Vector2D(X_Positions[i], BossZone_.y));
			attacking = true;
			canAttack = false;
		}
	}
	else waitingTime = SDL_GetTicks();
	
}