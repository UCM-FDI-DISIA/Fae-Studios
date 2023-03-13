#include "GrowVine.h"
#include "ColliderVine.h"
#include "../utils/checkML.h"


void GrowVine::update() {
	auto pos = tr_->getPosition();
	if (pos.getY() > posFinalT.getY()) {
		tr_->setPosition(Vector2D(pos.getX(), pos.getY() - 2));
	}
	if (cl_->getPos().getY() > posFinalC.getY()) {
		cl_->setPos(Vector2D(cl_->getPos().getX(), cl_->getPos().getY() - 2));
	}
}
void GrowVine::initComponent() {
	tr_ = ent_->getComponent<Transform>();
	cl_ = ent_->getComponent<ColliderVine>();
}