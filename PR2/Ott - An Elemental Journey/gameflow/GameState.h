#pragma once
#ifndef PROYECTOS2_GAMESTATE_H
#define PROYECTOS2_GAMESTATE_H

#include <list>
#include "../gameobjects/GameObject.h"
#include "../gameobjects/CollisionObject.h"


class SDLApplication; // Declaramos una clase SDLApplication para romper las dependencias circulares

/// Clase base que proporcionará funcionalidad a nuestros estados
class GameState {
protected:
    std::list<GameObject*> gameObjects; ///< Lista de gameObjects de nuestro juego
    SDLApplication* app = nullptr; ///< Puntero a la clase Game
    int stateID; ///< Identificador de nuestro estado
    bool deleted = false; ///< Booleano que indica si hay que borrar o no la escena (evitar problemas con iteradores)

    /// Constructora de la clase GameState
    /// \param stateID Identificador de nuestro estado
    /// \param app Puntero a la clase SDLApplication
    GameState(int stateID, SDLApplication* app) : app(app), stateID(stateID) {}

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
    virtual void handleEvents(SDL_Event& e);

    /// Devuelve el ID de la escena
    /// \return int con el ID de la escena
    virtual int getStateID() const { return stateID; };

    virtual void collision(CollisionObject* c);
};

#endif //PROYECTOS2_GAMESTATE_H
