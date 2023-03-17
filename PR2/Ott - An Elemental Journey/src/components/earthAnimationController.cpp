#include "earthAnimationController.h"
#include "PlayerAttack.h"

void earthAnimationController::setState(int newState, int col) {
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


void earthAnimationController::initComponent() {
	image = ent_->getComponent<FramedImage>();
	playerAttack = mngr_->getPlayer()->getComponent<PlayerAttack>();
	setState(ADVANCE);
}

void earthAnimationController::update() {
	int state = currentAnimation;
	timer_++;

	int col = image->getCurrentCol();
	//Si la columna es distinta a la última de la animación aumentamos col
	if (state == ADVANCE)
	{
		if (col != getNFrames(state) + getColNum(state) - 1) col = (timer_ / getTPerFrame(state)) % getNFrames(state) + startingCol;
	}
	else if (state == BACK)
	{
		if (col != getNFrames(state) - getColNum(state) - 1) col = startingCol - (timer_ / getTPerFrame(state)) % getNFrames(state) ;
	}
	image->setCol(col);

	if (timer_ > animationTime)
	{
		endAnim();
	}

}

void earthAnimationController::endAnim() {

	if (currentAnimation == ADVANCE)
	{
		setState(BACK);
	}
	else if (currentAnimation == BACK)
	{
		playerAttack->deleteEarthAttack();

	}
		
	timer_ = 0;
}