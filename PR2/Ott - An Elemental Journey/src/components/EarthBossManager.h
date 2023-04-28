#pragma once
#include "../utils/Vector2D.h"
#include "../ecs/Component.h"
#include "../ecs/anims.h"
#include <SDL.h>
#include"../ecs/Entity.h"
#include <vector>
#include "../ecs/anims.h"
#include "EarthBossAnimationController.h"
#include "CameraComponent.h"
#include "MapComponent.h"


class EarthBossManager : public Component
{
public:
    constexpr static ecs::cmpId_type id = ecs::_EARTHMNGR;
    EarthBossManager(SDL_Rect rD, MapComponent* map_);
    virtual ~EarthBossManager(){}
    void initializeEntities();
    void isFighting(bool b) { isFight = b; }
    inline void setState(int newState);
    void update() override;
    void initComponent() override;
    void die();
    void setChangeState(bool c) { changeState = c; }
    Entity* getHealthBar() { return healthBar; }
    void addPlatforms(std::vector<Entity*> pV) { platformVector = pV; }
private:
    //Dimensiones de la sala del boss de tierra
    SDL_Rect roomDimensions;

    //Entidades de juego 
    std::vector<Entity*> warningVector;
    std::vector<Entity*> vineVector;
    std::vector<Entity*> platformVector;
    MapComponent* map;
    Entity* healthBar;
    Entity* boss;
    Entity* presentBoss;
    Entity* pause;
    Entity* trigger;
    Entity* vinePlatform = nullptr;

    //Player referencia
    Entity* player = nullptr;
    Entity* refvine1 = nullptr;
    Entity* refvine2 = nullptr;
    Entity* refvine3 = nullptr;
    Entity* refvine4 = nullptr;
    int vine1 = -1;
    int vine2 = -1;
    int bossWarning = -1;
    int numRandVine = 0;
    Vector2D finPosBoss;
    Vector2D iniPosBoss;

    //Referencias
    EarthBossAnimationController* animController;

    //Variables numéricas
    int NUM_VINES = 6;
    int NUM_WARNINGS = 8;
    float offSet = 30;
    int verticalSpeed = 3;

    //Booleanos de juego
    bool isFight = false; // para empezar o acabar la partida
    bool attackingHorizontally = false;
    bool attackingVertically = false;

    //Métodos
    void verticalAttackPosition();
    void stateManagment();
    void horizontalAttack();
    void choosingVine();
    void createVinePlatform();

    //Vector de estados
    int actualState = 0;
    bool changeState = false;
    std::vector<EarthBossStates> states = { PRESENTATION, MINIPAUSE, WARNING,MINIPAUSE, ATTACKHORIZONTAL, PAUSE, WARNING, MINIPAUSE, ATTACKHORIZONTAL, PAUSE, WARNING,MINIPAUSE, ATTACKVERTICAL };

    

};

