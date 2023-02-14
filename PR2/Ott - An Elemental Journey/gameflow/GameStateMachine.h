#pragma once
#ifndef PROYECTOS2_GAMESTATEMACHINE_H
#define PROYECTOS2_GAMESTATEMACHINE_H

#include <stack>
#include "GameState.h"

/// Máquina de estados del juego
class GameStateMachine {
private:
    std::stack<GameState*> stateStack; ///< Pila que contiene los estados

public:
    /// Constructora de la máquina de estados
    GameStateMachine() = default;

    /// Destructora de la máquina de estados
    ~GameStateMachine() { emptyStack(); };

    /// Devuelve el estado actual
    /// \return Puntero al estado actual
    GameState* currentState() const;

    /// Mete un estado en la pila
    /// \param state Estado de juego
    void pushState(GameState* state);

    /// Cambia el primer estado de juego por uno dado
    /// \param state Estado de juego
    void changeState(GameState* state);

    /// Quita el último estado que ha entrado a la pila
    void popState();

    /// Comprueba si la pila está vacía
    bool empty();

    /// Vacía la pila
    void emptyStack();

    /// Quita el último estado que ha entrado a la pila y lo devuelve
    /// \return El último estado que ha entrado a la pila
    GameState* pop();
};

#endif //PROYECTOS2_GAMESTATEMACHINE_H
