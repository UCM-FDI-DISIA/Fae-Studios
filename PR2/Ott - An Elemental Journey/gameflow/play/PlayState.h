#include "../GameState.h"
#include <list>
#include "../../gameobjects/Entity.h"
#include "../../gameobjects/Mapa.h"
#include "../../gameobjects/Physics/Ground.h"
#include "../../ui/ScreenDarkener.h"
#include <iostream>
#include "../../gameobjects/Entity.h"
#include "../../ui/HealthBar.h"
#include "../SDL2_mixer/include/SDL_mixer.h"
#include "../../gameobjects/Bullet.h"
#pragma once

class Ott;
class InteractuableObject;
class Enredaderas;

using Camera = SDL_Rect;

const uint LEVEL_WIDTH = 8000;
const uint LEVEL_HEIGHT = 8000;
const auto CAM_OFFSET_HEIGHT = 0.73;
const int CAM_DEAD_ZONE = 350;

class PlayState : public GameState {
private:
    double gravity = 0.08f;
    list<Entity*> physicObjects;
    list<Ground*> groundObjects;
    list<Wall*> wallObjects;
    ScreenDarkener* screenDarkener;
    HealthBar* healthBar;
    list<InteractuableObject*> intObjects;
    list< Enredaderas*> eObjects;
    Camera camera;
    Ott* ott;
    Mapa* currentMap;
    Mix_Music* music;
    Vector2D collides(SDL_Rect Rect, SDL_Rect objRect);

public:
    PlayState(SDLApplication* app);
    ~PlayState();
    virtual void handleEvents();
    void ottCollide(const SDL_Rect& Ott, const SDL_Rect& onGround, SDL_Rect& grounRect, SDL_Rect& colRect, bool& ground
    , Vector2D& speed);
    virtual void update();
    inline double Gravity() { return gravity; };
    virtual void render() const;
    SDL_Rect ottPos() const;
    void setOttPos(const Vector2D& newPos);
    void climb();
    void moveCamera();
    void addEnredadera(const Vector2D& pos);
    void backToMenu();
    Vector2D checkCollisions();
    inline HealthBar* getHealthBar() { return healthBar; }
    inline list<Entity*> getEntityList() const { return physicObjects; }
    list<Entity*>::iterator getIteratorToFirstElement() { return physicObjects.begin(); }
    list<Entity*>::iterator getIteratorToEndElement() { return physicObjects.end(); }
    void addBullet(Vector2D pos, Vector2D dir, elementsInfo::elements elem, GameObject* g) {
        addObject(new Bullet(pos, app->getTexture("enemy", stateID), elem, g, dir, Scale(0.1f, 0.1f), this));
    }
    void addEntity(Entity* g) {
        addObject(g);
        physicObjects.push_back(g);
        auto it = physicObjects.end();
        it--;
        g->physicsIterator = it;
    }

    void deleteObject(Entity* obj);

    void enemyCollide(const SDL_Rect& enemyRect, const SDL_Rect& onGround, SDL_Rect& groundRect, SDL_Rect& colRect, bool& ground, bool& walled, Vector2D& speed);

    virtual void deleteObjects();

    void deleteEntities();
    
    bool bulletCollide(const SDL_Rect& bulletRect);

};