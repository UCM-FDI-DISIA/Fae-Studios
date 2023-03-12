#include "Manager.h"
#include "Entity.h"
#include "../game/Constructors.h"
#include "../components/AddVine.h"
#include "../components/Health.h"
#include "../components/InteractionComponent.h"
#include "../components/LampComponent.h"
#include "../components/PlayerAnimationComponent.h"

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

void Manager::createPlayer() {
    player = constructors::player(this, 200, 1300, 100, 120);
    camera = constructors::camera(this, 200, 700, 100, 120);
}

void Manager::createGrass(Vector2D position, int width, int height) {
    //constructors::grass(this, position, width, height);
}

void Manager::createLamp(int x1, int y1, int x2, int y2) {
    constructors::lamp(this, x1, y1, x2, y2);
}

void Manager::createSanctuary(Vector2D position, int width, int height) {
    constructors::sanctuary(this, position, width, height);
}

void Manager::createVine(Vector2D position, int width, int height) {
    constructors::vine(this, position, width, height);
}

void Manager::AddEnredadera(Manager* m) {
    Entity* aux = (*m->interactionIt);
    if (!(aux->getComponent<AddVine>()->doesntHaveVine())) {
        aux->getComponent<AddVine>()->setVine();
        Vector2D pos = Vector2D(aux->getComponent<Transform>()->getPosition().getX() + 5, aux->getComponent<Transform>()->getPosition().getY() - (&sdlutils().images().at("enredadera"))->height() * 1.25);
        m->createVine(pos);
    }
};

void Manager::checkInteraction() {
    bool interact = false;
    interactionIt = entsByGroup_[ecs::_grp_INTERACTION].begin();
    while (!interact && interactionIt != entsByGroup_[ecs::_grp_INTERACTION].end()) {
        Entity* ents = *interactionIt;
        SDL_Rect r1 = player->getComponent<Transform>()->getRect();
        SDL_Rect r2 = ents->getComponent<Transform>()->getRect();
        if (SDL_HasIntersection(&r1, &r2)) {
            ents->getComponent<InteractionComponent>()->interact();
            interact = true;
        }
        interactionIt++;
    }
}

void Manager::Teleport(Manager* m) {
    int cAnim = m->player->getComponent<PlayerAnimationComponent>()->getState();
    if (cAnim != IDLE && cAnim != RUN) return;
    Entity* aux = *m->interactionIt;
    Entity* tpLamp = aux->getComponent<LampComponent>()->getConnectedLamp();
    Vector2D newPos = tpLamp->getComponent<Transform>()->getPosition();
    m->player->getComponent<PlayerAnimationComponent>()->startTP(newPos);
}

void Manager::Save(Manager* m) {
    m->player->getComponent<Health>()->saveSactuary();
}
