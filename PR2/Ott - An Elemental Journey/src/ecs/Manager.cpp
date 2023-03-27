#include "Manager.h"
#include "Entity.h"
#include "../game/Constructors.h"
#include "../components/AddVine.h"
#include "../components/Health.h"
#include "../components/InteractionComponent.h"
#include "../components/LampComponent.h"
#include "../components/PlayerAnimationComponent.h"
#include "../components/ImageVine.h"
#include "../components/GrowVine.h"

Manager::Manager() : entsByGroup_() {
    deleted = false;
    for (auto& groupEntities : entsByGroup_) {
        groupEntities.reserve(100); //Reservamos un espacio de 100 entidades para cada uno de los grupos
    }
}

Manager::~Manager() {
    for (auto& ents : entsByGroup_) {
        for (auto e : ents)
            delete e; //Borramos todas las entidades
    }
}

Entity* Manager::addEntity(ecs::grpId_type gId) {
    Entity* e = new Entity(); //Creamos la entidad
    e->setAlive(true); //La ponemos "viva"
    e->setContext(this); //Le damos un contexto
    entsByGroup_[gId].push_back(e); //La pusheamos al vector del grupo correspondiente

    return e; //Y la devolvemos
}

void Manager::addToGroupList(ecs::grpId_type gId, Entity* e) {
    entsByGroup_[gId].push_back(e);
}

void Manager::refresh() {
    //Recorremos todos los grupos de nuestra matriz, comprobando si la entidad está o no viva.
    //Si no está viva, la eliminamos y la quitamos de la matriz
    for (ecs::grpId_type gId = 0; gId < ecs::maxGroupId; gId++) {
        auto& grpEnts = entsByGroup_[gId];
        grpEnts.erase(
            std::remove_if(grpEnts.begin(), grpEnts.end(),
                [](Entity* e) {
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

void Manager::saveToFile(std::ofstream& file) {
    for (auto& ents : entsByGroup_) {
        auto n = ents.size();
        for (auto i = 0u; i < n; i++)
            if (!deleted) ents[i]->saveToFile(file);
            else return;
    }
};

void Manager::loadFromFile(std::ifstream& file) {
    for (auto& ents : entsByGroup_) {
        auto n = ents.size();
        for (auto i = 0u; i < n; i++)
            if (!deleted) ents[i]->loadFromFile(file);
            else return;
    }
};

void Manager::update() {
    for (auto& ents : entsByGroup_) {
        auto n = ents.size();
        for (auto i = 0u; i < n; i++)
            if (!deleted) ents[i]->update();
            else return;
    }
}

void Manager::render() {
    for (auto& ents : entsByGroup_) {
        auto n = ents.size();
        for (auto i = 0u; i < n; i++)
            if (!deleted) ents[i]->render();
            else return;
    }
}




void Manager::handleInput() {
    for (auto& ents : entsByGroup_) {
        auto n = ents.size();
        for (auto i = 0u; i < n; i++)
            if (!deleted)ents[i]->handleInput();
            else return;
    }
}
