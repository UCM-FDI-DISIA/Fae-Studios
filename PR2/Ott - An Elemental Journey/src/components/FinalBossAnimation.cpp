#include "FinalBossAnimation.h"
#include "../states/PlayState.h"
#include "../states/GameStateMachine.h"
#include "Health.h"

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
	if (alive)
	{

	std::cout << currentAnimation << std::endl;
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

		if(state==DAMAGE_BOSS) 
		{
			image->setCol(getColNum(currentAnimation));
			image->setRow(getRowNum(currentAnimation));
		}
		else
		{
			int col = (timer_ / getTPerFrame(state)) % getNFrames(state) + getColNum(state);
			int c = getColNum(currentAnimation);
			image->setCol(col);
			image->setRow(getRowNum(state));
		}
		timer_++;
	
		if ((timer_ > (getTPerFrame(state) * getNFrames(state)) + 1)) {
			endAnim();													
		}
	}
	
	if (currentAnimation==IDLE_BOSS2)
	{
		if( SDL_GetTicks()  -moveTimer_> MOVE_TIME) { setState(IDLE_BOSS); }
	}
	
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
		alive = false;
	}
	else if (currentAnimation == IDLE_BOSS) setState(IDLE_BOSS2);
	else if (currentAnimation == DAMAGE_BOSS)setState(STUN_BOSS);
	else
	{
		timer_ = 0; row = getColNum(currentAnimation);
	}
	

}
