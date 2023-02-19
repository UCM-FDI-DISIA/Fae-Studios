#pragma once
#ifndef PROYECTOS2_GAMESTATE_H
#define PROYECTOS2_GAMESTATE_H

#include <list>
#include <stack>
#include "../gameobjects/Entity.h"
#include "../gameobjects/CollisionObject.h"


class SDLApplication; // Declaramos una clase SDLApplication para romper las dependencias circulares

enum STATEID{
    PLAY_STATE = 0,
    MAIN_MENU = 1,
    OPTIONS = 2,
    MUSIC_OPTIONS = 3,
    CONTROLS = 4,
    PAUSE_MENU = 5,
    



    NUMBER_OF_STATES
};

/// Clase base que proporcionará funcionalidad a nuestros estados
class GameState {
protected:
    std::list<GameObject*> gameObjects; ///< Lista de gameObjects de nuestro juego
    std::stack<GameObject*> deletedObjects;
    SDLApplication* app = nullptr; ///< Puntero a la clase Game
    STATEID stateID; ///< Identificador de nuestro estado
    bool deleted = false; ///< Booleano que indica si hay que borrar o no la escena (evitar problemas con iteradores)

    /// Constructora de la clase GameState
    /// \param stateID Identificador de nuestro estado
    /// \param app Puntero a la clase SDLApplication
    GameState(STATEID stateID, SDLApplication* app) : app(app), stateID(stateID) {}

public:
    /// Pone el booleano deleted en true, indicando que el estado debe borrarse
    void setDelete();

    /// Destructora de la clase GameState
    virtual ~GameState();

    /// Actualiza todos los gameobjects de la lista
    virtual void update();

    /// Renderiza todos los gameobjects de la lista
    virtual void render() const;

    /// Maneja los eventos de los gameobjects de la lista
    /// \param e SDL_Event con el evento
    virtual void handleEvents();

    /// Devuelve el ID de la escena
    /// \return int con el ID de la escena
    virtual STATEID getStateID() const { return stateID; };

    virtual void collision(CollisionObject* c);

    GameObject* addObject(GameObject* obj);

    void deleteObject(Entity* obj);

    virtual void deleteObjects();
};

#endif //PROYECTOS2_GAMESTATE_H
