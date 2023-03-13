#include "VineManager.h"

void VineManager::createVine() {
    vine = mngr_->addEntity(ecs::_grp_VINE);
    vine->addComponent<Transform>(iniPos, width, height);
}

void VineManager::addVine() {
    if (!hasVine) {
        switch (texture_){
        case NORMAL:  vine->addComponent<ImageVine>(&sdlutils().images().at("enredadera"), rotation); break;
            case EVIL: vine->addComponent<ImageVine>(&sdlutils().images().at("vine"), rotation); break;
        }
        SDL_Rect dest;
        dest = vine->getComponent<Transform>()->getRect();
        Entity* player = mngr_->getPlayer();
        dest.h -= player->getComponent<Transform>()->getRect().h / 2.5;
        vine->addComponent<ColliderVine>(dest, Vector2D(finPos.getX(), finPos.getY() + player->getComponent<Transform>()->getRect().h / 2));
        vine->addComponent<GrowVine>(finPos, speed, dir);
        hasVine = true;
    }
}