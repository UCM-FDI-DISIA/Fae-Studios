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
    tr = ent_->getComponent<Transform>();
}

void Bullet::update()
{
    if (SDL_GetTicks() - startTime >= maxTime * 1000) ent_->setAlive(false); //Destruye las balas tras un tiempo
    else {
        SDL_Rect trigger = tr->getRect();
        auto enemiesGrp = mngr_->getEntities(ecs::_grp_CHARACTERS);
        for (auto e : enemiesGrp) {
            SDL_Rect rect = e->getComponent<PhysicsComponent>()->getCollider();
            SDL_Rect result;
            if (e != instigator && SDL_IntersectRect(&rect, &trigger, &result)) {
                bool dir = true;
                if (result.x + result.w > rect.x + rect.w / 2) dir = false;
                else dir = true;
                e->getComponent<Health>()->recieveDamage(elem, dir);
                ent_->setAlive(false);
            }
        }
    }
}
