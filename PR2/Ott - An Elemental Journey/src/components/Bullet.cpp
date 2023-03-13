#include "Bullet.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "Health.h"
#include "../utils/checkML.h"
#include <SDL.h>
#include "../states/GameStateMachine.h"
#include "../states/PlayState.h"

void Bullet::initComponent()
{
    player = mngr_->getPlayer();
    physics = ent_->getComponent<PhysicsComponent>();
    physics->setGravity(false);
    startTime = SDL_GetTicks();
}

void Bullet::update()
{
    if (SDL_GetTicks() - startTime >= maxTime * 1000) ent_->setAlive(false); //Destruye las balas tras un tiempo
    else {
        auto tr = ent_->getComponent<Transform>();
        SDL_Rect trigger = { (int)tr->getPosition().getX(), (int)tr->getPosition().getY(), (int)tr->getWidth(), (int)tr->getHeight() };
        auto enemiesGrp = mngr_->getEntities(ecs::_grp_CHARACTERS);
        for (auto e : enemiesGrp) {
            SDL_Rect rect = e->getComponent<PhysicsComponent>()->getCollider();
            if (e != instigator && SDL_HasIntersection(&rect, &trigger)) {
                e->getComponent<Health>()->recieveDamage(instigator->getComponent<Health>()->getElement());
                ent_->setAlive(false);
            }
        }
    }
}
