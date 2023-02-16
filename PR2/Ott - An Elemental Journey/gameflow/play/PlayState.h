#include "../GameState.h"
#include <list>
#include "../../gameobjects/Entity.h"
#include "../../gameobjects/Mapa.h"
#include "../../gameobjects/Physics/Ground.h"
#include <iostream>
#include "../../gameobjects/Entity.h"
#pragma once

class Ott;
class InteractuableObject;
class Enredaderas;

using Camera = SDL_Rect;

const uint LEVEL_WIDTH = 8000;
const uint LEVEL_HEIGHT = 8000;
const auto CAM_OFFSET_HEIGHT = 0.78;
const int CAM_DEAD_ZONE = 300;

class PlayState : public GameState {
private:
    double gravity = 0.08f;
    Ground* gr;
    Ground* gr1;
    Ground* gr2;
    Ground* grT;
    list<Entity*> physicObjects;
    list<Ground*> groundObjects;
    list<Wall*> wallObjects;
    list<InteractuableObject*> intObjects;
    list< Enredaderas*> eObjects;
    Camera camera;
    Ott* ott;
    Mapa* currentMap;
    Vector2D collides(SDL_Rect Rect, SDL_Rect objRect);
public:
    PlayState(SDLApplication* app);
    virtual void handleEvents();
    void ottCollide(const SDL_Rect& Ott, const SDL_Rect& onGround, SDL_Rect& grounRect, SDL_Rect& colRect, bool& ground
    , const Vector2D& speed);
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
};