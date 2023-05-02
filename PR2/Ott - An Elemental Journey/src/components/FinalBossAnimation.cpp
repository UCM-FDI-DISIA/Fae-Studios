#include "FinalBossAnimation.h"
#include "../states/PlayState.h"
#include "../states/GameStateMachine.h"

FinalBossAnimation::~FinalBossAnimation()
{
	if (!ent_->isAlive())static_cast<PlayState*>(GameStateMachine::instance()->currentState())->eraseEnemy(posInList, roomNum);
}

void FinalBossAnimation::initComponent()
{
	image = ent_->getComponent<FramedImage>();
	//health_ = ent_->getComponent<Health>();
	setState(IDLE_BOSS);
	image->setCol(0); image->setRow(0);
	row = 0;
}

void FinalBossAnimation::update()
{
	if (currentAnimation == IDLE_BOSS) 
	{ 
		int state = currentAnimation;
		int c = (timer_ / getTPerFrame(state)) % getNFrames(state) + getColNum(state);
		timer_++;
		col = c % 15;
		if (col==0)
		{
			row = (c / 15);
		}
		image->setRow(row); image->setCol(col); 
		if ((timer_ > (getTPerFrame(state) * getNFrames(state)) + 1)) {
			endAnim(); row = getRowNum(IDLE_BOSS);
		}
		//std::cout << col << " " << row << std::endl;
	}
	else
	{
		int state = currentAnimation;
		int col = (timer_ / getTPerFrame(state)) % getNFrames(state) + getColNum(state);
		int c = getColNum(currentAnimation);
		timer_++;
	
		image->setCol(col);
		image->setRow(getRowNum(state));
		if ((timer_ > (getTPerFrame(state) * getNFrames(state)) + 1)) {
			endAnim();													
		}

	}
}

void FinalBossAnimation::setState(int newState)
{
	if (currentAnimation != newState) {
		currentAnimation = newState;
		timer_ = 0;
	}
}

void FinalBossAnimation::endAnim()
{
	if (currentAnimation == DIE_BOSS) {
		ent_->setAlive(false);
	}
	if (currentAnimation == STUN_BOSS) currentAnimation = IDLE_BOSS;
	if (currentAnimation == IDLE_BOSS) { timer_ = 0; }
}
