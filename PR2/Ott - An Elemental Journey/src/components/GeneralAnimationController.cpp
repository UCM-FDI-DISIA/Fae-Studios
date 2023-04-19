#include "GeneralAnimationController.h"
#include "../ecs/Entity.h"
#include "FramedImage.h"
#include "../states/PlayState.h"


GeneralAnimationController::GeneralAnimationController(anims::Entities e, Entity* e1)
{
	eAnims = e;
	image = e1->getComponent<FramedImage>();
	
}

void GeneralAnimationController::update() {
	timer_++;
	int col = image->getCurrentCol();
	col = (timer_ / getTPerFrame()) % getNFrames() + getColNum();
	image->setCol(col);
}