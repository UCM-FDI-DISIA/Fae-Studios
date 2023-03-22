#include "FireBossAnimation.h"
#include "FramedImage.h"
void FireBossAnimation::initComponent()
{
	image = ent_->getComponent<FramedImage>();
	eFireBossComponent_ = ent_->getComponent<FireBossComponent>();
	timer_ = 0;
	setState(IDLE_FIREBOSS);

}
void FireBossAnimation::update()
{
	image->setCol(0); image->setRow(0);
	
	int c = getColNum(currentAnimation);

	
	int state = currentAnimation;
	timer_++;
	int col = (timer_ / getTPerFrame(state)) % getNFrames(state) + getColNum(state);
	image->setCol(col);
	image->setRow(getRowNum(state));
	//std::cout << col << std::endl;
	
	if (timer_ > 150)
	{

	//image->setCol(image->getCurrentCol()+1);
	timer_ = 0;
	}
	
}

void FireBossAnimation::setState(int newState)
{
	currentAnimation = newState;
}

