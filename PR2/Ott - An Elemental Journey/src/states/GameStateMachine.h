#pragma once

#include <deque>
#include "GameState.h"
#include "../utils/Singleton.h"

/// Máquina de estados del juego
class GameStateMachine : public Singleton<GameStateMachine>{
    friend Singleton<GameStateMachine>;
private:
	std::deque<GameState*> stateStack; ///< Deque que contiene los estados (ha sido cambiada de una pila para mejor acceso)

    /// Constructora de la máquina de estados
    GameStateMachine() = default;

public:
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

    void resetStack();

    /// Devuelve el estado de juego, aprovechando que siempre va a estar, y que va a estar al fondo de la pila
    /// \return Puntero al estado de juego
    GameState* getPlayState() const {return stateStack.back();}

    /// Quita el último estado que ha entrado a la pila
	void popState(bool deleting = false);

    /// Comprueba si la pila está vacía
	bool empty();

    /// Vacía la pila
	void emptyStack();

    /// Renderiza todos los estados que encontramos en la pila
    void renderAllStates();

    /// Refresca todos los estados que encontramos en la pila
    void refreshAllStates();

    /// Quita el último estado que ha entrado a la pila y lo devuelve
    /// \return El último estado que ha entrado a la pila
	GameState* pop();
};

inline GameStateMachine& stateMachine() {
    return *GameStateMachine::instance();
}

