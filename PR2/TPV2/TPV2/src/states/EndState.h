#pragma once
#include "GameState.h"

/// Estado del fin del juego
class EndState : public GameState {
public:
    /// Constructora del estado de fin del juego
    EndState();

    /// Maneja el input del estado
    void handleInput() override;
};

