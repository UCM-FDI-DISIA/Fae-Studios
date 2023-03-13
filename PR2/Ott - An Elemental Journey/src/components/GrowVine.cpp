#include "GrowVine.h"

void GrowVine::update() {
    if (tr_->getPosition().getY() > posFinalT.getY()) {
        tr_->setPosition(Vector2D(tr_->getPosition().getX(), tr_->getPosition().getY() + dir * speed));
    }
}
void GrowVine::initComponent()
{
    tr_= ent_->getComponent<Transform>();
}