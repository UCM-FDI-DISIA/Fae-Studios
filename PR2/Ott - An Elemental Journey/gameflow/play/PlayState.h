#include "../GameState.h"
#include <list>
#include "../../gameobjects/Entity.h"
#include "../../gameobjects/Physics/Ground.h"
#include <iostream>
#pragma once

class PlayState : public GameState {
private:
    double gravity = 0.08f;
    Ground* gr;
    list<Entity*> physicObjects;
    list<Ground*> groundObjects;
    list<Wall*> wallObjects;

public:
    PlayState(SDLApplication* app);
    void ottCollide(const SDL_Rect& Ott, const SDL_Rect& onGround, SDL_Rect& colRect, bool& col, bool& ground);
    virtual void update();
    inline double Gravity() { return gravity; };
};