#include "GrowVine.h"
#include "ColliderVine.h"


void GrowVine::update() {
	if (tr_->getPos().getY() > posFinalT.getY()) {
		tr_->setPos(Vector2D(tr_->getPos().getX(), tr_->getPos().getY() - 2));
	}
	if (cl_->getPos().getY() > posFinalC.getY()) {
		cl_->setPos(Vector2D(cl_->getPos().getX(), cl_->getPos().getY() - 2));
	}
}
void GrowVine::initComponent()
{
	tr_ = ent_->getComponent<Transform>();
	cl_ = ent_->getComponent<ColliderVine>();
}