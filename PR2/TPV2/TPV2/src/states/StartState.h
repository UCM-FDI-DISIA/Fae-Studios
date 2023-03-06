#pragma once
#ifndef TPV2_STARTSTATE_H
#define TPV2_STARTSTATE_H
#include "GameState.h"

/// Estado de inicio de partida
class StartState : public GameState{
public:
    /// Constructora del estado
    StartState();

    void handleInput() override;
};


#endif //TPV2_STARTSTATE_H
