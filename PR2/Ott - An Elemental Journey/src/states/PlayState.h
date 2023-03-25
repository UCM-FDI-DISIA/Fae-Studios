#pragma once
#include "GameState.h"
#include <SDL_mixer.h>
#include "../ecs/Entity.h"
#include "../components/MapComponent.h"
#include "../components/EnemyAnimationController.h"
#include <list>

/// Estado de juego
class PlayState : public GameState {
private:    
    void checkCollisions(std::list<Entity*> entities);
    std::vector<Entity*>::const_iterator interactionIt;

    Entity* player_;
    Entity* camera_;
    Entity* earthBoss_;
    MapComponent* map_;
    Entity* lastSanctuary;
    std::vector<std::list<Entity*>> enemies, initialEnemies;
    std::vector<std::vector<std::list<Entity*>::iterator>> enemyIt;

    float gravityValue = 0.2;

public:
    /// Constructora del estado de juego
    PlayState();

    /// Destructora del estado de juego
    ~PlayState() override;

    /// Actualiza variables del estado y de sus entidades
    void update() override;

    void resetFade() override;

    /// Bloquea el uso del teclado después de volver del menú de pausa
    void blockKeyboardInputAfterUnfreeze();

    std::pair<bool, bool> checkCollisionWithVine();
    
    inline void addEnemy(Entity* enemy, int room) { 
        enemies[room].push_front(enemy);
        enemyIt[room].push_back(enemies[room].begin());
        enemy->getComponent<EnemyAnimationComponent>()->setPosInList(enemyIt[room].size() - 1, room);
    };

    inline void initEnemies(int numRooms) {
        for (int i = 0; i < numRooms; ++i) {
            enemies.push_back({});
            enemyIt.push_back({});
        }
    }

    void eraseEnemy(int itPos, int numRoom) {
        int room = map_->getCurrentRoom();
        enemies[numRoom].erase(enemyIt[numRoom][itPos]);
    }
    void resetEnemies() 
    { 
        for (int i = 0; i < enemies.size(); ++i) {
            for (auto it : enemies[i]) {
                it->setAlive(false);
            }
        }
        mngr_->refresh();
        enemies.clear();
        enemyIt.clear();
        map_->generateEnemies();
    }
    void handleInput() override;

    inline Entity* getPlayer() { return player_; }
    inline Entity* getCamera() { return camera_; }
    inline Entity* getEarthBoss() { return earthBoss_; }
    inline Entity* getCurrentInteraction() const { return *interactionIt; }
    inline float getGravityValue() const { return gravityValue; }
    void checkInteraction();
    void AddEnredadera();
    void AddLifeShard();
    void Teleport();
    void Save();
    void endRest();
    inline std::vector<std::list<Entity*>> getEnemies() { return enemies; }
};

