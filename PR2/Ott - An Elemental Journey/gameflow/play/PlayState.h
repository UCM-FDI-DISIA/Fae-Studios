#include "../GameState.h"
#include <list>
#include "../../gameobjects/Entity.h"
#include "../../gameobjects/Mapa.h"
#include "../../gameobjects/Physics/Ground.h"
#include <iostream>
#include "../../gameobjects/Entity.h"
#pragma once

class Ott;

using Camera = SDL_Rect;

const uint LEVEL_WIDTH = 1800;
const uint LEVEL_HEIGHT = 80000;

class PlayState : public GameState {
private:
    double gravity = 0.08f;
    Ground* gr;
    list<Entity*> physicObjects;
    list<Ground*> groundObjects;
    list<Wall*> wallObjects;
    Mapa* currentMap;
    Camera camera;
    Ott* ott;

public:
    PlayState(SDLApplication* app);
    void ottCollide(const SDL_Rect& Ott, const SDL_Rect& onGround, SDL_Rect& colRect, bool& col, bool& ground);
    virtual void update();
    inline double Gravity() { return gravity; };
    void handleEvents(SDL_Event& e) override;
    virtual void render() const;
    void backToMenu();
};