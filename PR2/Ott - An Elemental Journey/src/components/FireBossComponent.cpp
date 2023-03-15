#include "FireBossComponent.h"
#include "Bullet.h"
#include "FirePillarComponent.h"
#include "Transform.h"
#include "../game/Constructors.h"
FireBossComponent::FireBossComponent()
{

}

void FireBossComponent::initComponent()
{
	tr_ = ent_->getComponent<Transform>();
	player = mngr_->getPlayer();
}

void FireBossComponent::update()
{
	if (SDL_GetTicks() - specialAttackTimer >= timeSpecialAttack * 1000) {
		std::cout << "Ataque especial" << std::endl;
		specialAttackTimer = SDL_GetTicks();
		normalAttackTimer = SDL_GetTicks();
		startSpecialAttack();
	}
	else if (SDL_GetTicks() - normalAttackTimer >= timeNormalAttack * 1000) {
		std::cout << "Ataque normal" << std::endl;
		normalAttackTimer = SDL_GetTicks();
	}
}
void FireBossComponent::startSpecialAttack()
{
	Vector2D pPos = player->getComponent<Transform>()->getPosition();
	if (abs(pPos.getY() - ent_->getComponent<Transform>()->getPosition().getY()) > ent_->getComponent<Transform>()->getHeight()) {
		shootAtPlayer();
	}
	else spawnPillars();
	
}
void FireBossComponent::spawnPillars()
{
	Transform* pTr = player->getComponent<Transform>();
	Vector2D pPos = player->getComponent<Transform>()->getPosition();
	constructors::firePillar(mngr_, "lamp", pPos.getX() + pTr->getWidth()/2, ent_->getComponent<Transform>()->getPosition().getY() + ent_->getComponent<Transform>()->getHeight(), 1);
}

void FireBossComponent::shootAtPlayer()
{
	Vector2D position = tr_->getPosition();
	Transform* pTr = player->getComponent<Transform>();
	Vector2D direction = pTr->getPosition() - position; 
	direction = direction.normalize() * 2;
	constructors::bullet(mngr_, "lamp", position.getX(), position.getY(), 50, direction, ent_, ecs::Fire, 1);
}


