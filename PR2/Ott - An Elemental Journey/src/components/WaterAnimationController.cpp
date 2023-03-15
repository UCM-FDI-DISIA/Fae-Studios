#include "WaterAnimationController.h"
#include "PlayerAttack.h"

void WaterAnimationController::setState(int newState, int col) {
	currentAnimation = newState;
	timer_ = 0;
	image->setCol(getColNum(currentAnimation));
	if (col != -1)
	{
		animationTime = getTPerFrame(currentAnimation) * (col + 1) + 1;
		startingCol = col;
	}
	else {
		animationTime = (getTPerFrame(currentAnimation) * getNFrames(currentAnimation)) + 1;
		startingCol = getColNum(currentAnimation);
	}
}


void WaterAnimationController::initComponent() {
	image = ent_->getComponent<FramedImage>();
	playerAttack = mngr_->getPlayer()->getComponent<PlayerAttack>();
	setState(WATER_ADVANCE);
}

void WaterAnimationController::update() {
	int state = currentAnimation;
	timer_++;

	int col = image->getCurrentCol();
	//Si la columna es distinta a la última de la animación aumentamos col
	if (state == WATER_ADVANCE)
	{
		if (col != getNFrames(state) + getColNum(state) - 1) col = (timer_ / getTPerFrame(state)) % getNFrames(state) + startingCol;
	}
	else if (state == WATER_BACK)
	{
		image->setRow(1);
		if (col != getNFrames(state) - getColNum(state) - 1) col = startingCol - (timer_ / getTPerFrame(state)) % getNFrames(state);
	}
	image->setCol(col);

	if (timer_ > animationTime)
	{
		endAnim();
	}

}

void WaterAnimationController::endAnim() {

	if (currentAnimation == WATER_ADVANCE)
	{
		setState(WATER_BACK);
	}
	else if (currentAnimation == WATER_BACK)
	{
		playerAttack->deleteWaterAttack();

	}

	timer_ = 0;
}