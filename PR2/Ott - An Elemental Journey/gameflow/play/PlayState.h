#include "../GameState.h"
#include <list>
#include "../../gameobjects/Physics/Ground.h"
#include <iostream>
#include "../../gameobjects/Entity.h"
#pragma once

class Ott;
class InteractuableObject;
class Enredaderas;

using Camera = SDL_Rect;

const uint LEVEL_WIDTH = 1800;
const uint LEVEL_HEIGHT = 800;

class PlayState : public GameState {
private:
    double gravity = 0.08f;
    Ground* gr;
    list<Entity*> physicObjects;
    list<Ground*> groundObjects;
    list<Wall*> wallObjects;
    list<InteractuableObject*> intObjects;
    list< Enredaderas*> eObjects;
    Camera camera;
    Ott* ott;
public:
    static bool Interacting;
    static bool IsInteracting() { return Interacting; };
    PlayState(SDLApplication* app);
    virtual void handleEvents(SDL_Event& e);
    void ottCollide(const SDL_Rect& Ott, const SDL_Rect& onGround, SDL_Rect& colRect, bool& col, bool& ground);
    virtual void update();
    inline double Gravity() { return gravity; };
    virtual void render() const;
    SDL_Rect ottPos() const;
    void setOttPos(const Vector2D& newPos);
    void addEnredadera(const Vector2D& pos);
};