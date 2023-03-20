#include "GrowVine.h"

void GrowVine::update() {
    if (grow) {
        if (orientation == "vertical") {
            if (dir < 0 && tr_->getPosition().getY() > posFinalT.getY() || dir > 0 && tr_->getPosition().getY() < posFinalT.getY()) {
                tr_->setPosition(Vector2D(tr_->getPosition().getX(), tr_->getPosition().getY() + (dir * speed)));
            }
        }
        else {
            if (dir < 0 && tr_->getPosition().getX() > posFinalT.getX() || dir > 0 && tr_->getPosition().getX() < posFinalT.getX()) {
                tr_->setPosition(Vector2D(tr_->getPosition().getX() + (dir * speed), tr_->getPosition().getY()));
            }
        }

    }
}
void GrowVine::initComponent()
{
    tr_= ent_->getComponent<Transform>();
}