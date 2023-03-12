#pragma once
#include "GameState.h"
#include <SDL_mixer.h>

/// Estado de juego
class PlayState : public GameState {
private:
    Mix_Music* music;
    
    void checkCollisions();
    std::vector<Entity*>::const_iterator interactionIt;

public:
    /// Constructora del estado de juego
    PlayState();

    /// Destructora del estado de juego
    ~PlayState() override;

    /// Actualiza variables del estado y de sus entidades
    void update() override;

    /// Bloquea el uso del teclado después de volver del menú de pausa
    void blockKeyboardInputAfterUnfreeze();
    std::pair<bool, bool> checkCollisionWithVine();
    

    void handleInput() override;

};

