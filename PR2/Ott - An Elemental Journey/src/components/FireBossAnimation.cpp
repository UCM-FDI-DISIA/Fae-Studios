#include "FireBossAnimation.h"
#include "FramedImage.h"
void FireBossAnimation::initComponent()
{
	image = ent_->getComponent<FramedImage>();
	eFireBossComponent_ = ent_->getComponent<FireBossComponent>();
	timer_ = 0;
	setState(IDLE_FIREBOSS);
	image->setCol(0); image->setRow(0);
}
void FireBossAnimation::update()
{
	
	
	int c = getColNum(currentAnimation);
	
	int state = currentAnimation;
	timer_++;
	int col = (timer_ / getTPerFrame(state)) % getNFrames(state) + getColNum(state);
	image->setCol(col);
	image->setRow(getRowNum(state));
	//std::cout << currentAnimation << std::endl;
	if ((timer_ > (getTPerFrame(state) * getNFrames(state)) + 1)) {// si el timer ha superado al tiempo de cada frame * los frames 
		endAnim();													// que tiene la animación actual, se llama a endAnim();
	}

}

void FireBossAnimation::endAnim()
{
	if (currentAnimation == DIE_FIREBOSS) {
		ent_->setAlive(false);
	}
	if (currentAnimation == ATTACK_FIREBOSS) {
		auto fComp = ent_->getComponent<FireBossComponent>();
		if(fComp->isMoving()) currentAnimation = AMBUSH_FIREBOSS;
		else currentAnimation = IDLE_FIREBOSS;
	}
	
}

void FireBossAnimation::setState(int newState)
{
	if (currentAnimation != newState) {
		currentAnimation = newState;
		timer_ = 0;
	}
}

