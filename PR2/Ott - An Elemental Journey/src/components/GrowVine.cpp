#include "GrowVine.h"

void GrowVine::update() {
    if (grow) {
        auto posX = tr_->getPosition().getX(); auto posY = tr_->getPosition().getY();
        if (orientation == "vertical") {
            if (!reached && dir < 0 && posY > posFinalT.getY() || !reached && dir > 0 && posY < posFinalT.getY()) {
                tr_->setPosition(Vector2D(posX, posY + (dir * speed)));
            }
            else if (!reached && dir < 0 && posY <= posFinalT.getY() || !reached && dir > 0 && posY >= posFinalT.getY()) {
                reached = true;
            }
            else if (reached && goesBack && posY != posIni.getY()) {
                tr_->setPosition(Vector2D(posX, posY + ((-1*dir) * speed)));
            }
            else if (reached && posY == posIni.getY()) {
                reached = false; grow = false;   
            }
        }
        else {
            if (!reached && dir < 0 && posX > posFinalT.getX() || !reached && dir > 0 && posX < posFinalT.getX()) {
                tr_->setPosition(Vector2D(posX + (dir * speed), posY));
            }
            else if (!reached && dir < 0 && posX <= posFinalT.getX() || !reached && dir > 0 && posX >= posFinalT.getX()) {
                reached = true;
            }
            else if (reached && goesBack && posX != posIni.getX()) {
                tr_->setPosition(Vector2D(posX + ((-1*dir) * speed), posY));
            }
            else if (reached && posX == posIni.getX()) {
                reached = false; grow = false;
            }
        }
    }
}
void GrowVine::initComponent()
{
    tr_= ent_->getComponent<Transform>();
    posIni = ent_->getComponent<Transform>()->getPosition();
}