#pragma once
#include "../utils/Vector2D.h"
#include "../ecs/Component.h"
#include "../ecs/anims.h"
#include <SDL.h>
#include"../ecs/Entity.h"
#include <vector>
#include "../ecs/anims.h"
#include "EarthBossAnimationController.h"


enum EarthBossStates{PRESENTATION, WARNING, ATTACKVERTICAL, ATTACKHORIZONTAL, PAUSE};
class EarthBossManager : public Component
{
    struct Warnings {
        Entity* warning;
        int num;
    };
    struct Platforms {
        Entity* platform;
        int num;
    };
public:
    constexpr static ecs::cmpId_type id = ecs::_EARTHMNGR;
    EarthBossManager(SDL_Rect rD);
    virtual ~EarthBossManager(){}
    void isFighting(bool b) { isFight = b; }
    void initializeEntities();
    inline void setState(int newState);
private:
    //Dimensiones de la sala del boss de tierra
    SDL_Rect roomDimensions;

    //Entidades de juego
    std::vector<Warnings> warningVector;
    std::vector<Entity*> vineVector;
    std::vector<Platforms> platformVector;
    Entity* boss;
    Entity* presentBoss;
    Entity* pause;

    //Player referencia
    Entity* player;

    //Referencias
    EarthBossAnimationController* animController;
    int state;

    //Variables numéricas
    int NUM_VINES = 3;
    int NUM_WARNINGS = 8;
    float offSet = 30;

    //Booleanos de juego
    bool isFight = false; // para empezar o acabar la partida

    //Métodos
    void verticalAttackPosition();
    void initializeEntities();
    void update() override;
    void initComponent() override;
};

