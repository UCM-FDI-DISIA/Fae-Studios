#include "BossHealthBar.h"
#include "EarthBossManager.h"
#include "Health.h"
#include "FireBossRoom.h"

void BossHealthBar::initComponent() {
	posBar = { offset * 2, sdlutils().height() - (offset * 2), sdlutils().width() - (offset * 4), offset * 2 };
	posLife = posBar; posLife.w -= 20; posLife.y += 5;
	maxWidth = posLife.w;
}

void BossHealthBar::damage(int n) {
	int hit = maxWidth / BossLife;
	/*for(int i = 0; i < n; ++i)*/ posLife.w -= hit; // yo me rindo ya 
}

void BossHealthBar::reset() {
	posLife.w = posBar.w;
}

void BossHealthBar::die() {
	isDead = true;
	if (actualBoss == Earth) bossManager->getComponent<EarthBossManager>()->die();
}

void BossHealthBar::render() {
	if (!isDead && actualBoss == Fire && mngr_->getFireBoss()->getComponent<Health>()->getHealth() <= 0) isDead = true;

	if (!isDead && actualBoss == Earth && bossManager->getComponent<EarthBossManager>()->getShowBar()) {
		if (mngr_->getPlayer()->getComponent<Health>()->getHealth() <= 0) {
			reset();
		}
		barTx->render(posBar);
		lifeTx->render(posLife);
	}
	else if (!isDead && mngr_->getFireBoss()->getComponent<Health>()->getHealth() > 0 && actualBoss == Fire && mngr_->getFireBossRoom()->getComponent<FireBossRoom>()->getShowBar()) {
		barTx->render(posBar);
		lifeTx->render(posLife);
	}
	else if(!isDead && actualBoss != Earth && actualBoss != Fire) {
		barTx->render(posBar);
		lifeTx->render(posLife);
	}
}
