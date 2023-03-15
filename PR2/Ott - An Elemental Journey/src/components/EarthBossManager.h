#pragma once
#include "../utils/Vector2D.h"
#include "../ecs/Component.h"
#include "../ecs/anims.h"
#include <SDL.h>
#include"../ecs/Entity.h"
#include <vector>
class EarthBossManager : public Component
{
    struct Warnings {
        Entity* warning;
        int num;
    };
public:
    constexpr static ecs::cmpId_type id = ecs::_EARTHMNGR;
    EarthBossManager(SDL_Rect rD, Entity* b) : roomDimensions(rD), presentBoss(b) {
        initializeEntities();
    }
    virtual ~EarthBossManager(){}
private:
    SDL_Rect roomDimensions;
    std::vector<Warnings> warningVector;
    std::vector<Entity*> vineVector;
    Entity* boss;
    Entity* presentBoss;
    int NUM_VINES = 3;
    int NUM_WARNINGS = 8;
    float offSet = 30;
    void initializeEntities();
    void verticalAttackPosition();
};

