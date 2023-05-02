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
	int row = image->getCurrentRow();
	int c = (timer_ / getTPerFrame()) % getNFrames() + getColNum();
	col = c % image->getTexture()->getNumCols();
	if (col == 0) {
		row = (c / image->getTexture()->getNumCols());
	}
	image->setCol(col); image->setRow(row);
}