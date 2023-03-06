#pragma once
#include "GameState.h"
#include "../game/AsteroidsManager.h"

/// Estado de juego
class PlayState : public GameState {
private:
    AsteroidsManager* asteroidsManager; ///< Manager de asteroides

public:
    /// Constructora del estado de juego
    PlayState();

    /// Destructora del estado de juego
    ~PlayState() override;

    /// Comprueba si las balas o la nave han chocado contra un asteroide
    void checkCollisions();

    /// Actualiza variables del estado y de sus entidades
    void update() override;

    /// Reinicia el estado después de que se acabe una ronda
    void initAfterFreeze();

    /// Bloquea el uso del teclado después de volver del menú de pausa
    void blockKeyboardInputAfterUnfreeze();


    void handleInput() override;
};

