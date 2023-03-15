#include "FireBossComponent.h"
#include "Bullet.h"
#include "FirePillarComponent.h"
#include "Transform.h"

FireBossComponent::FireBossComponent()
{

}

void FireBossComponent::initComponent()
{
	tr_ = ent_->getComponent<Transform>();
}

void FireBossComponent::update()
{
	if (SDL_GetTicks() - specialAttackTimer >= timeSpecialAttack * 1000) {
		std::cout << "Ataque especial" << std::endl;
		specialAttackTimer = SDL_GetTicks();
		normalAttackTimer = SDL_GetTicks();
	}
	else if (SDL_GetTicks() - normalAttackTimer >= timeNormalAttack * 1000) {
		std::cout << "Ataque normal" << std::endl;
		normalAttackTimer = SDL_GetTicks();
	}
}
