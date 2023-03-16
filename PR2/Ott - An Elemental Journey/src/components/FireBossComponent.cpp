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
		ambushing = true;
	}
	if (ambushing) { ambush(); }
	else if (retirada)
	{
		int speed = 2;
		if (tr_->getPosition().getX() - tr_->getInitialPosition().getX() > 0) { speed = -speed; }
		tr_->setPosition(Vector2D(tr_->getPosition().getX() + speed, tr_->getPosition().getY()));
		if (tr_->getPosition().getX() == tr_->getInitialPosition().getX()) { retirada = false; }
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
void FireBossComponent::ambush()
{
	Transform* playerTr = player->getComponent<Transform>();
	Health* playerH = player->getComponent<Health>();
	std::vector<Entity*> ground = mngr_->getEntities(ecs::_grp_GROUND);

	//colliders jugador, boss
	SDL_Rect collider = tr_->getRect();
	SDL_Rect playerCollider = playerTr->getRect();
	SDL_Rect collision;

	bool collided = false;
	int speed;

	//direccion en que hacer la emboscada
	if (tr_->getPosition().getX() - playerTr->getPosition().getX() > 0) { speed = -ambushSpeed; }
	else { speed = ambushSpeed; }
	tr_->setPosition(Vector2D(tr_->getPosition().getX() + speed, tr_->getPosition().getY()));

	//colisiones con ott, paredes como condicion de paro de la emboscada
	//ott
	bool interseccion = SDL_IntersectRect(&collider, &playerCollider, &collision);
	if (interseccion)
	{
		ambushing = false; playerH->recieveDamage(ecs::Fire); retirada = true;
	}
	//wall
	else
	{
		for (Entity* g : ground) {
			SDL_Rect r2 = g->getComponent<Transform>()->getRect();
			bool interseccion = SDL_IntersectRect(&collider, &r2, &collision);
			if (interseccion && (collision.w < collision.h)) { ambushing = false; retirada = true; }
		}
	}
}


