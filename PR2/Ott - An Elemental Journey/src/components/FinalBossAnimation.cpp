#include "FinalBossAnimation.h"
#include "../states/PlayState.h"
#include "../states/GameStateMachine.h"

//FinalBossAnimation::~FinalBossAnimation()
//{
//	if (!ent_->isAlive())static_cast<PlayState*>(GameStateMachine::instance()->currentState())->eraseEnemy(posInList, roomNum);
//}

void FinalBossAnimation::initComponent()
{
	image = ent_->getComponent<FramedImage>();
	//health_ = ent_->getComponent<Health>();
	setState(IDLE_BOSS2);
	image->setCol(0); image->setRow(0);
	row = 0;
	moveTimer_ = SDL_GetTicks();
	MOVE_TIME = (getNFrames(IDLE_BOSS2) * getTPerFrame(IDLE_BOSS2) )* 10;
}

void FinalBossAnimation::update()
{
	if (currentAnimation == IDLE_BOSS) 
	{ 
		int state = currentAnimation;
		int c = (timer_ / getTPerFrame(state)) % getNFrames(state) + getColNum(state);
		timer_++;
		col = c % 14;
		if (col==0)
		{
			row = (c / 14);
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
	
	if (currentAnimation==IDLE_BOSS2)
	{
		if( SDL_GetTicks()  -moveTimer_> MOVE_TIME) { setState(IDLE_BOSS); }
	}
	
}

void FinalBossAnimation::setState(int newState)
{
	if (currentAnimation != newState) {
		currentAnimation = newState;
		timer_ = 0;
		if(newState==IDLE_BOSS2){ moveTimer_ = SDL_GetTicks(); }
	}
}

void FinalBossAnimation::endAnim()
{
	if (currentAnimation == DIE_BOSS) {
		ent_->setAlive(false);
	}
	//else if (currentAnimation == STUN_BOSS) setState(IDLE_BOSS2);
	else if (currentAnimation == IDLE_BOSS) setState(IDLE_BOSS2);
	else
	{
		timer_ = 0; row = getColNum(currentAnimation);
	}
	

}
