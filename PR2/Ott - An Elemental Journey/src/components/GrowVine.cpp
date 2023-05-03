#include "GrowVine.h"
#include "../sdlutils/SoundEffect.h"
#include "../sdlutils/SDLUtils.h"
#include"VineManager.h"

void GrowVine::update() {
    if (grow) {
        auto posX = tr_->getPosition().getX(); auto posY = tr_->getPosition().getY();
        if (orientation == "vertical") {
            if (!reached && dir < 0 && posY > posFinalT.getY() || !reached && dir > 0 && posY < posFinalT.getY()) {
                tr_->setPosition(Vector2D(posX, posY + (dir * speed)));
                if (!SoundEffect::isSoundBeingPlayed(ecs::_channel_AMBIENTAL)) sdlutils().soundEffects().at("grow_vine").play(0, ecs::_channel_AMBIENTAL);
            }
            else if (!reached && dir < 0 && posY <= posFinalT.getY() || !reached && dir > 0 && posY >= posFinalT.getY()) {
                reached = true;
                SoundEffect::fadeOutChannel(250, ecs::_channel_AMBIENTAL);
            }
            else if (reached && goesBack && posY != posIni.getY()) {
                tr_->setPosition(Vector2D(posX, posY + ((-1*dir) * speed)));
                if (!SoundEffect::isSoundBeingPlayed(ecs::_channel_AMBIENTAL)) sdlutils().soundEffects().at("grow_vine").play(0, ecs::_channel_AMBIENTAL);
            }
            else if (reached && posY == posIni.getY()) {
                reached = false; grow = false;
                SoundEffect::fadeOutChannel(250, ecs::_channel_AMBIENTAL);
            }
        }
        else {
            if (!reached && dir < 0 && posX > posFinalT.getX() || !reached && dir > 0 && posX < posFinalT.getX()) {
                tr_->setPosition(Vector2D(posX + (dir * speed), posY));
                if (!SoundEffect::isSoundBeingPlayed(ecs::_channel_AMBIENTAL)) sdlutils().soundEffects().at("grow_vine").play(0, ecs::_channel_AMBIENTAL);
            }
            else if (!reached && dir < 0 && posX <= posFinalT.getX() || !reached && dir > 0 && posX >= posFinalT.getX()) {
                reached = true;
                SoundEffect::fadeOutChannel(250, ecs::_channel_AMBIENTAL);
            }
            else if (reached && goesBack && posX != posIni.getX()) {
                tr_->setPosition(Vector2D(posX + ((-1*dir) * speed), posY));
                if (!SoundEffect::isSoundBeingPlayed(ecs::_channel_AMBIENTAL)) sdlutils().soundEffects().at("grow_vine").play(0, ecs::_channel_AMBIENTAL);
            }
            else if (reached && posX == posIni.getX()) {
                reached = false; grow = false;
                SoundEffect::fadeOutChannel(250, ecs::_channel_AMBIENTAL);
            }
        }
    }
    if (ungrow) {
        auto posX = tr_->getPosition().getX(); auto posY = tr_->getPosition().getY();
        if (orientation == "vertical") {
            if (!reached && dir < 0 && posY <= posIni.getY() || !reached && dir > 0 && posY >= posIni.getY()) {
                tr_->setPosition(Vector2D(posX, posY - (dir * speed)));
            }
            else if (!reached && dir < 0 && posY > posIni.getY() || !reached && dir > 0 && posY < posIni.getY()) {
                reached = true;
                vManager->setHasVine();
                //ent_->setAlive(false);
                ent_->removeComponent<ColliderVine>();
            }
            else if (reached && goesBack && posY != posFinalT.getY()) {
                tr_->setPosition(Vector2D(posX, posY - ((-1 * dir) * speed)));
                vManager->setHasVine();
                ent_->setAlive(false);
       
            }
            else if (reached && posY == posFinalT.getY()) {
                reached = false; grow = false;
                vManager->setHasVine();
                ent_->setAlive(false);
            }
        }
        else {
            if (!reached && dir < 0 && posX <= posIni.getX() || !reached && dir > 0 && posX >= posIni.getX()) {
                tr_->setPosition(Vector2D(posX - (dir * speed), posY));
            }
            else if (!reached && dir < 0 && posX > posIni.getX() || !reached && dir > 0 && posX < posIni.getX()) {
                reached = true;
            }
            else if (reached && goesBack && posX != posFinalT.getX()) {
                tr_->setPosition(Vector2D(posX - ((-1 * dir) * speed), posY));
                ent_->setActive(false);
            }
            else if (reached && posX == posFinalT.getX()) {
                reached = false; grow = false;
                ent_->setActive(false);
            }
        }
    }
}
void GrowVine::initComponent()
{
    tr_= ent_->getComponent<Transform>();
    posIni = ent_->getComponent<Transform>()->getPosition();
}