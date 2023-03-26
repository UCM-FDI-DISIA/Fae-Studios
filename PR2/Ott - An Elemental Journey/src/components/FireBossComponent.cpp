#include "FireBossComponent.h"
#include "Bullet.h"
#include "FirePillarComponent.h"
#include "PhysicsComponent.h"
#include"FireBossAnimation.h"
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
	if (fAnim_->getState() == DIE_FIREBOSS) return;
	//Esto aqui esta feisimo pero es que no entiendo ahora mateix porque no lo coge
	p = ent_->getComponent<PhysicsComponent>();
	speed = 0;
	if (stunned) {
		if (SDL_GetTicks() - stunTimer > timeStunned * 1000) {
			stunned = false;
		}
		else return;
	}
	if (SDL_GetTicks() - specialAttackTimer >= timeSpecialAttack * 1000) {
		std::cout << "Ataque especial" << std::endl;
		specialAttackTimer = SDL_GetTicks();
		//normalAttackTimer = SDL_GetTicks();
		startSpecialAttack();
	}
	else if (!retirada && !ambushing) {
		std::cout << "Ataque normal" << std::endl;
		//normalAttackTimer = SDL_GetTicks();
		startNormalAttack();
	}
	if (ambushing) 
	{ 
		ambush();
		if(fAnim_->getState() != DIE_FIREBOSS && fAnim_->getState() != ATTACK_FIREBOSS) fAnim_->setState(AMBUSH_FIREBOSS);
	}
	else if (retirada && fAnim_->getState() != ATTACK_FIREBOSS)
	{
		//direccion
		if (tr_->getPosition().getX() - tr_->getInitialPosition().getX() > 0) { speed = -rSpeed; p->lookDirection(false); }
		else{ speed = rSpeed; p->lookDirection(true); }
		//movimiento hacia su posicion incial
		tr_->setPosition(Vector2D(tr_->getPosition().getX() + speed, tr_->getPosition().getY()));
		//si ha llegado
		if (tr_->getPosition().getX() == tr_->getInitialPosition().getX()) 
		{ 
			retirada = false; fAnim_->setState(IDLE_FIREBOSS);
			normalAttackTimer = SDL_GetTicks();
		}
	}
	
}
void FireBossComponent::startSpecialAttack()
{
	Vector2D pPos = player->getComponent<Transform>()->getPosition();
	if (abs(pPos.getY() - ent_->getComponent<Transform>()->getPosition().getY()) > ent_->getComponent<Transform>()->getHeight()) {
		//shootAtPlayer();
	}
	else spawnPillars();
	
}
void FireBossComponent::startNormalAttack()
{
	Vector2D pPos = player->getComponent<Transform>()->getPosition();
	if ((abs(pPos.getY() - ent_->getComponent<Transform>()->getPosition().getY()) > ent_->getComponent<Transform>()->getHeight() ) && (SDL_GetTicks() - normalAttackTimer >= timeNormalAttack * 1000)) {
		shootAtPlayer();
		normalAttackTimer = SDL_GetTicks();
		
	}
	else if(!ambushing && (SDL_GetTicks() - normalAttackTimer >= timeNormalAttack * 1000)){
		ambushing = true;
	}
}
void FireBossComponent::spawnPillars()
{
	Transform* pTr = player->getComponent<Transform>();
	Vector2D pPos = player->getComponent<Transform>()->getPosition();
	constructors::firePillar(mngr_, "firePillar", pPos.getX() - pTr->getWidth()/2, ent_->getComponent<Transform>()->getPosition().getY() + ent_->getComponent<Transform>()->getHeight()/2, 1);
}

void FireBossComponent::shootAtPlayer()
{
	if (fAnim_->getState() != DIE_FIREBOSS) fAnim_->setState(ATTACK_FIREBOSS);
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
	SDL_Rect collider = tr_->getRect(); collider.x = collider.x + collider.w / 4;
	collider.w = collider.w / 2;
	SDL_Rect playerCollider = playerTr->getRect();
	SDL_Rect collision;

	bool collided = false;
	int speed;

	//direccion en que hacer la emboscada
	if (tr_->getPosition().getX() - playerTr->getPosition().getX() > 0) { speed = -ambushSpeed; p->lookDirection(false); }
	else { speed = ambushSpeed; p->lookDirection(true); }
	tr_->setPosition(Vector2D(tr_->getPosition().getX() + speed, tr_->getPosition().getY()));

	//colisiones con ott, paredes como condicion de paro de la emboscada
	//ott
	bool interseccion = SDL_IntersectRect(&collider, &playerCollider, &collision);
	if (interseccion)
	{
		ambushing = false; playerH->recieveDamage(ecs::Fire); retirada = true;
		fAnim_->setState(ATTACK_FIREBOSS);
	}
	//wall
	else
	{
		for (Entity* g : ground) {
			SDL_Rect r2 = g->getComponent<Transform>()->getRect();
			bool interseccion = SDL_IntersectRect(&collider, &r2, &collision);
			if (interseccion && (collision.w < collision.h)) 
			{ 
				ambushing = false; retirada = true;
			}
		}
	}
}

void FireBossComponent::stunBoss()
{
	stunned = true; 
	stunTimer = SDL_GetTicks();
}
void FireBossComponent::combo()
{
	
}


