#include "../checkML.h"
#include "GameState.h"
#include "../SDLApplication.h"
#include "../loaders/TextureLoader.h"


GameState::~GameState() {
    for (auto e : gameObjects) delete(e); //Borramos todos los objetos de la lista
    app->getTextureManager()->unregisterTexture(getStateID());
}

void GameState::update() {
    //Recorremos la lista para actualizar los objetos,
    // y en caso de que se haya borrado un elemento en la lista, dejamos de recorrerla
    for (auto it = gameObjects.begin(); it != gameObjects.end() && !deleted;) {
        (*it)->update();
        if (!deleted) ++it;
        else return;
    }
}

void GameState::render() const {
    //Recorremos la lista para renderizar los objetos,
    // y en caso de que se haya borrado un elemento en la lista, dejamos de recorrerla
    for (auto it = gameObjects.begin(); it != gameObjects.end() && !deleted;) {
        (*it)->render();
        if (!deleted) ++it;
        else return;
    }
}

void GameState::handleEvents(SDL_Event& e) {
    //Recorremos la lista para manejar los eventos de los objetos,
    // y en caso de que se haya borrado un elemento en la lista, dejamos de recorrerla
    for (auto it = gameObjects.begin(); it != gameObjects.end() && !deleted;) {
        (*it)->handleEvents(e);
        if (!deleted) ++it;
        else return;
    }
}

void GameState::setDelete() {
    deleted = true;
}

GameObject* GameState::addObject(GameObject* obj) {
    gameObjects.push_back(obj);
    auto it = gameObjects.end();
    --it;
    obj->it = it;
    return obj;
}

void GameState::deleteObject(GameObject* obj) {
    deletedObjects.push(obj);
}

void GameState::deleteObjects() {
    while (!deletedObjects.empty()) {
        auto obj = deletedObjects.top();
        obj->getState()->gameObjects.erase(obj->it);
        deletedObjects.pop();
        delete obj;
    }
}