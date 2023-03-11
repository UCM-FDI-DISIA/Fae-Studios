#include "Bullet.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "Health.h"
#include "../utils/checkML.h"
#include "SDL.h"

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
        SDL_Rect trigger = { tr->getPosition().getX(), tr->getPosition().getY(), tr->getWidth(), tr->getHeight() };
        auto enemiesGrp = mngr_->getEntities(ecs::_grp_CHARACTERS);
        for (auto e : enemiesGrp) {
            SDL_Rect rect = e->getComponent<Transform>()->getRect();
            if (e != instigator && SDL_HasIntersection(&rect, &trigger)) {
                e->getComponent<Health>()->recieveDamage(instigator->getComponent<Health>()->getElement());
                ent_->setAlive(false);
            }
        }
    }
}
