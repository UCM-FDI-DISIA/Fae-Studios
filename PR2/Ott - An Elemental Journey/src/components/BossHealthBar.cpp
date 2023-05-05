#include "BossHealthBar.h"
#include "EarthBossManager.h"
#include "FinalBossAnimation.h"
#include "Health.h"
#include "FireBossRoom.h"

void BossHealthBar::initComponent() {
	posBar = { offset * 2, sdlutils().height() - (offset * 2), sdlutils().width() - (offset * 4), offset * 2 };
	posLife = posBar; posLife.w -= 20; posLife.y += 5;
	maxWidth = posLife.w;
}

void BossHealthBar::damage(int n) {
	int hit = n / (double)BossLife * maxWidth;
	posLife.w -= hit; 
	std::cout << hit << std::endl;
	if (actualBoss == Final&&!isDead) { bossManager->getComponent<FinalBossAnimation>()->setState(DAMAGE_BOSS); }
}

void BossHealthBar::cure(int n) {
  	int hit = n / (double)BossLife * maxWidth;
	if (posLife.w + hit < maxWidth)
	{
		posLife.w += hit;
		std::cout << hit << std::endl;
	}
	else posLife.w = maxWidth;
}

void BossHealthBar::reset() {
	posLife.w = posBar.w;
}

void BossHealthBar::die() {
	isDead = true;
	if (actualBoss == Earth) bossManager->getComponent<EarthBossManager>()->die();
	else if (actualBoss == Final) bossManager->getComponent<FinalBossAnimation>()->setState(DIE_BOSS);
}

void BossHealthBar::render() {
	if (!isDead && actualBoss == Fire && mngr_->getFireBoss()->hasComponent<Health>()&&mngr_->getFireBoss()->getComponent<Health>()->getHealth() <= 0) isDead = true;

	if (!isDead && actualBoss == Earth && bossManager->getComponent<EarthBossManager>()->getShowBar()) {
		if (mngr_->getPlayer()->getComponent<Health>()->getHealth() <= 0) {
			reset();
		}
		barTx->render(posBar);
		lifeTx->render(posLife);
	}
	else if (!isDead && actualBoss == Fire && mngr_->getFireBoss()->hasComponent<Health>()&&mngr_->getFireBoss()->getComponent<Health>()->getHealth() > 0 && mngr_->getFireBossRoom()->getComponent<FireBossRoom>()->getShowBar()) {
		barTx->render(posBar);
		lifeTx->render(posLife);
	}
	else if(!isDead && actualBoss != Earth && actualBoss != Fire) {
		barTx->render(posBar);
		lifeTx->render(posLife);
	}
}
