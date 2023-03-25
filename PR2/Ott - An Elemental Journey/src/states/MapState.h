#pragma once
#include "GameState.h"
#include <SDL_mixer.h>
#include "../ecs/Entity.h"
#include "../components/MapComponent.h"
#include "../components/EnemyAnimationController.h"
#include <list>
#include <vector>
#include "GameState.h"
#include "../game/ecs.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"
#include "../states/GameStateMachine.h"

class PlayState;

class MapState : public GameState
{
private:
    bool exit = false;
public:
    /// Constructora del estado de juego
    MapState(PlayState* ps);

    /// Destructora del estado de juego
    ~MapState() override;

    virtual void update();
};


