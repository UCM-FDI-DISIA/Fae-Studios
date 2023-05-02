#pragma once
#include "GameState.h"
#include <SDL_mixer.h>
#include "../ecs/Entity.h"
#include "../components/MapComponent.h"
#include "../components/EnemyAnimationController.h"
#include "../components/FireBossAnimation.h"
#include "../components/LoreRoom.h"
#include "../components/InteractionComponent.h"
#include <list>
#include <vector>
#include "../game/ecs.h"

/// Estado de juego
class PlayState : public GameState {
private:    
    void checkCollisions(std::list<Entity*> entities);
    std::vector<Entity*>::const_iterator interactionIt;
    std::vector<std::vector<bool>> visitedRooms;

    Entity* player_;
    Entity* camera_;
    Entity* earthBoss_;
    Entity* screenDarkener_;
    MapComponent* map_;
    Entity* lastSanctuary=nullptr;
    std::vector<std::list<Entity*>> enemies = {}, initialEnemies = {};
    std::vector<std::list<Entity*>> carteles = {};
    std::vector<std::vector<std::list<Entity*>::iterator>> enemyIt;
    ecs::maps currentMap;

    float gravityValue = 0.2;

    bool isScreenDarkened = false;

public:
    /// Constructora del estado de juego
    PlayState();
    PlayState(std::string fileName);

    /// Destructora del estado de juego
    ~PlayState() override;

    /// Actualiza variables del estado y de sus entidades
    void update() override;

    void resetFade() override { sdlutils().musics().at(sdlutils().levels().at(map_->getCurrentLevel()).bgsong).resumeMusic(); }

    /// Bloquea el uso del teclado después de volver del menú de pausa
    void blockKeyboardInputAfterUnfreeze();

    std::pair<bool, bool> checkCollisionWithVine();
    
    inline void addEnemy(Entity* enemy, int room) { 
        enemies[room].push_front(enemy);
        enemyIt[room].push_back(enemies[room].begin());
        if (enemy->hasComponent<EnemyAnimationComponent>()) enemy->getComponent<EnemyAnimationComponent>()->setPosInList(enemyIt[room].size() - 1, room);
        else if(enemy->hasComponent<FireBossAnimation>()) enemy->getComponent<FireBossAnimation>()->setPosInList(enemyIt[room].size() - 1, room);
        
    };

    inline void addCarteles(Entity* cartel, int room) {
        carteles[room].push_front(cartel);
    };

    inline void initEnemies(int numRooms) {
        for (int i = 0; i < numRooms; ++i) {
            enemies.push_back({});
            enemyIt.push_back({});
        }
    }

    inline void initCarteles(int numRooms) {
        for (int i = 0; i < numRooms; ++i) {
            carteles.push_back({});
        }
    }

    inline void eraseCarteles(int numRooms) {
        if (carteles.size() > 0) {
            for (auto c : carteles) {
                if (c.size() > 0) {
                    for (auto cartel : c) {
                        cartel->setAlive(false);
                    }
                }
            }
        }
        carteles.clear();
    }

    inline void initVisitedRooms(int numRooms) {
        visitedRooms[currentMap].reserve(numRooms);
        visitedRooms[currentMap].push_back(true);
        for (int i = 1; i < numRooms; ++i) {
            visitedRooms[currentMap].push_back(false);
        }
    }

    inline void setVisited(int room) {
        visitedRooms[currentMap][room] = true;
    }

    inline bool isVisited(ecs::maps map, int room) { return visitedRooms[map][room]; }

    inline MapComponent* getMap() { return map_; }

    void eraseEnemy(int itPos, int numRoom) {
        int room = map_->getCurrentRoom();
        enemies[numRoom].erase(enemyIt[numRoom][itPos]);
    }
    void resetEnemies() { 
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

    inline void interact() { (*interactionIt)->getComponent<InteractionComponent>()->interact(); }
    inline Entity* getPlayer() { return player_; }
    inline Entity* getCamera() { return camera_; }
    inline Entity* getEarthBoss() { return earthBoss_; }
    inline Entity* getCurrentInteraction() const { return *interactionIt; }
    inline float getGravityValue() const { return gravityValue; }
    void checkInteraction();
    void AddEnredadera();
    void startLore();
    void AddLifeShard(int id);
    void Teleport();
    void Save();
    void UnlockElement(ecs::elements elem);
    void endRest();
    inline std::vector<std::list<Entity*>> getEnemies() { return enemies; }
    inline std::vector<std::list<Entity*>> getCarteles() { return carteles; }
    inline ecs::maps getCurrentMap() { return currentMap; }
    inline void changeMap(int map) { currentMap = (ecs::maps)map; enemies.clear(); 
        initialEnemies.clear(); enemyIt.clear(); };
};