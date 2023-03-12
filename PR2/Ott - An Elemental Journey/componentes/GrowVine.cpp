#include "GrowVine.h"


void GrowVine::update() {
	if (tr_->getPos().getY() > posFinalT.getY()) {
		tr_->setPos(Vector2D(tr_->getPos().getX(), tr_->getPos().getY() - 2));
	}
}
void GrowVine::initComponent()
{
	tr_ = ent_->getComponent<Transform>();
}