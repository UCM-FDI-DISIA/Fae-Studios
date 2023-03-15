#pragma once
#include "GameState.h"
#include <SDL_mixer.h>
#include "../ecs/Entity.h"
#include "../components/MapComponent.h"

/// Estado de juego
class PlayState : public GameState {
private:
    Mix_Music* music;
    
    void checkCollisions(std::vector<Entity*> entities);
    std::vector<Entity*>::const_iterator interactionIt;

    Entity* player_;
    Entity* camera_;
    MapComponent* map_;
    std::vector<std::vector<Entity*>> enemies;

    float gravityValue = 0.2;

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
    
    void setEnemies(const std::vector<std::vector<Entity*>>& enemies) { this->enemies = enemies; };

    void handleInput() override;

    inline Entity* getPlayer() { return player_; }
    inline Entity* getCamera() { return camera_; }
    inline Entity* getCurrentInteraction() const { return *interactionIt; }
    inline float getGravityValue() const { return gravityValue; }
    void checkInteraction();
    void AddEnredadera();
    void Teleport();
    void Save();

};

