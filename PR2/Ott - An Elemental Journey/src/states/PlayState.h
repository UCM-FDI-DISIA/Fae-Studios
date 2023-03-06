#pragma once
#include "GameState.h"

/// Estado de juego
class PlayState : public GameState {
private:

public:
    /// Constructora del estado de juego
    PlayState();

    /// Destructora del estado de juego
    ~PlayState() override;

    /// Actualiza variables del estado y de sus entidades
    void update() override;

    /// Bloquea el uso del teclado después de volver del menú de pausa
    void blockKeyboardInputAfterUnfreeze();

    void handleInput() override;
};

