#include "../GameState.h"
#include <list>
#include "../../gameobjects/Physics/Ground.h"
#include <iostream>
#include "../../gameobjects/Entity.h"
#include "../SDL2_mixer/include/SDL_mixer.h"
#pragma once

class Ott;

using Camera = SDL_Rect;

const uint LEVEL_WIDTH = 1800;
const uint LEVEL_HEIGHT = 800;

class PlayState : public GameState {
private:
    double gravity = 0.08f;
    Ground* gr;
    Ground* gr2;
    list<Entity*> physicObjects;
    list<Ground*> groundObjects;
    list<Wall*> wallObjects;
    Camera camera;
    Ott* ott;
    Mix_Music* music;

public:
    PlayState(SDLApplication* app);
    ~PlayState();
    void ottCollide(const SDL_Rect& Ott, const SDL_Rect& onGround, SDL_Rect& colRect, bool& col, bool& ground);
    virtual void update();
    inline double Gravity() { return gravity; };
    virtual void render() const;
    void backToMenu();
    inline list<Entity*> getEntityList() const { return physicObjects; }
};