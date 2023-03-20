#include "GrowVine.h"

void GrowVine::update() {
    if (orientation == "vertical") {
        if (!reached && dir < 0 && tr_->getPosition().getY() > posFinalT.getY() || !reached && dir > 0 && tr_->getPosition().getY() < posFinalT.getY()) {
            tr_->setPosition(Vector2D(tr_->getPosition().getX(), tr_->getPosition().getY() + (dir * speed)));
        }
        else if (!reached && dir < 0 && tr_->getPosition().getY() <= posFinalT.getY() || !reached && dir > 0 && tr_->getPosition().getY() >= posFinalT.getY()) {
            reached = true;
        }
        else if (reached && goesBack && tr_->getPosition().getY() != posIni.getY()) {
            tr_->setPosition(Vector2D(tr_->getPosition().getX(), tr_->getPosition().getY() + ((-1*dir) * speed)));
        }
    }
    else {
        if (!reached && dir < 0 && tr_->getPosition().getX() > posFinalT.getX() || !reached && dir > 0 && tr_->getPosition().getX() < posFinalT.getX()) {
            tr_->setPosition(Vector2D(tr_->getPosition().getX() + (dir * speed), tr_->getPosition().getY()));
        }
        else if (!reached && dir < 0 && tr_->getPosition().getX() <= posFinalT.getX() || !reached && dir > 0 && tr_->getPosition().getX() >= posFinalT.getX()) {
            reached = true;
        }
        else if (reached && goesBack && tr_->getPosition().getX() != posIni.getX()) {
            tr_->setPosition(Vector2D(tr_->getPosition().getX() + ((-1*dir) * speed), tr_->getPosition().getY()));
        }
    }
}
void GrowVine::initComponent()
{
    tr_= ent_->getComponent<Transform>();
    posIni = ent_->getComponent<Transform>()->getPosition();
}