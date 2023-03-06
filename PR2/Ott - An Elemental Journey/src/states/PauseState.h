#pragma once
#include "GameState.h"

/// Estado de pausa del juego
class PauseState : public GameState {
public:
    /// Constructor del estado de pausa
	PauseState();

    /// Maneja el input del estado
	void handleInput() override;
};

