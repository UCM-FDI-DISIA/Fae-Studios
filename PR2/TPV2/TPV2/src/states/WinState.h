#pragma once
#include "GameState.h"

/// Estado de victoria de la partida
class WinState : public GameState {
public:
    /// Constructora del estado
	WinState();
	void handleInput() override;
};

