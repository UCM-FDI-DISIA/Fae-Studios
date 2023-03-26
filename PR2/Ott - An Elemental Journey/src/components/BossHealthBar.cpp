#include "BossHealthBar.h"
#include "Health.h"

void BossHealthBar::initComponent() {
	posBar = { offset * 2, sdlutils().height() - (offset * 2), sdlutils().width() - (offset * 4), offset * 2 };
	posLife = posBar; posLife.w -= 20; posLife.y += 5;
	maxWidth = posLife.w;
}

void BossHealthBar::damage(int n) {
	int hit = maxWidth / 10;
	/*for(int i = 0; i < n; ++i)*/ posLife.w -= hit; // yo me rindo ya 
}

void BossHealthBar::reset() {
	posLife.w = posBar.w;
}

void BossHealthBar::render() {
	barTx->render(posBar);
	lifeTx->render(posLife);
}
