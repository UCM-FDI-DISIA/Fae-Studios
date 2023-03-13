//LIMPIO -> A FALTA DE CAMBIAR EL MANAGER

#pragma once
#include "PhysicsComponent.h"

class Bullet : public Component
{
private:
    Entity* player;
    Entity* instigator; //Se usa para saber quien ha lanzado el ataque y que no le afecte
    ecs::elements elem;
    PhysicsComponent* physics;
    int startTime, maxTime = 4;
public:
    constexpr static ecs::cmpId_type id = ecs::_BULLET;
    Bullet(ecs::elements e, Entity* inst) : Component(), player(nullptr), elem(e), physics(nullptr), instigator(inst) {};
    void initComponent() override;
    virtual void update();
    inline ecs::elements getElem() { return elem; }
};

