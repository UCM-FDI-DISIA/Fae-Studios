#include "Manager.h"
#include "Entity.h"
#include "../SDLApplication.h"
Manager::Manager(SDLApplication* g) : entsByGroup_(), game(g)
{
    
    for (auto& groupEntities : entsByGroup_) {
        groupEntities.reserve(100);
    }
}

Entity* Manager::addEntity(ecs::grpId_type gId = ecs::_grp_GENERAL)
{
    Entity* e = new Entity();
    e->setAlive(true);
    e->setContext(this);
    entsByGroup_[gId].push_back(e);
    return e;
}

void Manager::refresh()
{
    for (ecs::grpId_type gId = 0; gId < ecs::maxGroupId; gId++) {
        auto& grpEnts = entsByGroup_[gId];
        grpEnts.erase(
            std::remove_if(grpEnts.begin(), grpEnts.end(), [](Entity* e) {
                    if (e->isAlive()) {
                        return false;
                    }
                    else {
                        delete e;
                        return true;
                    }
            }),
            grpEnts.end());
    }
}

void Manager::update()
{
    for (auto& ents : entsByGroup_) {
        auto n = ents.size();
        for (auto i = 0u; i < n; i++)
            ents[i]->update();
    }
}

void Manager::render()
{
    for (auto& ents : entsByGroup_) {
        auto n = ents.size();
        for (auto i = 0u; i < n; i++)
            ents[i]->render();
    }
}

void Manager::createPlayer()
{
    Entity* e = addEntity(ecs::_grp_CHARACTERS);
    e->addComponent<Transform>(100, 100, 100, 120);
    e->addComponent<FramedImage>(game->getTexture("ott_water", PLAY_STATE), 9,8);
}

const vector<Entity*>& Manager::getEntitiesByGroup(grpId_type gId = ecs::_grp_GENERAL)
{
    return entsByGroup_[gId];
}

void Manager::addToGroupList(grpId_type gId, Entity* e)
{
    entsByGroup_[gId].push_back(e);
}

Manager::~Manager()
{
    for (auto& ents : entsByGroup_) {
        for (auto e : ents)
            delete e;
    }
}
