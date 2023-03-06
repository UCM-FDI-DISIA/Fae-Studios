#pragma once
#ifndef TPV2_ENDOFROUNDSTATE_H
#define TPV2_ENDOFROUNDSTATE_H
#include "GameState.h"

/// Estado del fin de la ronda (cuando morimos pero seguimos teniendo vidas)
class EndOfRoundState : public GameState {
public:
    /// Constructora del estado de fin de ronda
    EndOfRoundState();

    /// Maneja el input del estado
    void handleInput() override;
};


#endif //TPV2_ENDOFROUNDSTATE_H
