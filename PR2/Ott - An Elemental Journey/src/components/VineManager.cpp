#include "VineManager.h"

void VineManager::createVine() {
    switch (texture_) {
        case NORMAL: vine = mngr_->addEntity(ecs::_grp_VINE); break;
        case EVIL: vine = mngr_->addEntity(ecs::_grp_GROUND); break;
    }
    vine->addComponent<Transform>(iniPos, width, height);
}

void VineManager::addVine() {
    if (!hasVine) {
        switch (texture_) {
             case NORMAL:  vine->addComponent<ImageVine>(&sdlutils().images().at("enredadera"), rotation, true); break;
             case EVIL: vine->addComponent<ImageVine>(&sdlutils().images().at("vine"), rotation, false); break;
        }
        SDL_Rect dest;
        dest = vine->getComponent<Transform>()->getRect();
        Entity* player = mngr_->getPlayer();
        dest.h -= player->getComponent<Transform>()->getRect().h / 2.5;
        vine->addComponent<ColliderVine>(dest, Vector2D(finPos.getX(), finPos.getY() + player->getComponent<Transform>()->getRect().h / 2));
        vine->addComponent<GrowVine>(finPos, speed, dir, "vertical", false, this);
        hasVine = true;
    }
}