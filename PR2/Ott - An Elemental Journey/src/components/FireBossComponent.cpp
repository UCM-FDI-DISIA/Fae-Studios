#include "FireBossComponent.h"
#include "Bullet.h"
#include "FirePillarComponent.h"
#include "PhysicsComponent.h"
#include"FireBossAnimation.h"
#include "Transform.h"
#include "FramedImage.h"
#include "../game/Constructors.h"
FireBossComponent::FireBossComponent()
{

}

void FireBossComponent::initComponent()
{
	tr_ = ent_->getComponent<Transform>();
	player = mngr_->getPlayer();
	endY = tr_->getPosition().getY();
	startX = tr_->getPosition().getX();
	startPosition();
	
}
void FireBossComponent::startPosition()
{
	tr_->setPosition(Vector2D{ tr_->getPosition().getX(), tr_->getPosition().getY() - 2000 });
}
void FireBossComponent::update()
{
	//Casos donde el boss no puede hacer nada (cuando cae en la presentación, cuando se muere, y si está estuneado)
	if (fAnim_->getState() == DIE_FIREBOSS || !start) return;

	if (falling) {
		if (tr_->getPosition().getY() + tr_->getHeight()*0.75 < endY) {
			tr_->setPosition(Vector2D{ tr_->getPosition().getX(), (float)(tr_->getPosition().getY() + 30) });
			return;
		}
		else {
			tr_->setPosition(Vector2D{ tr_->getPosition().getX(),(float)(endY - tr_->getHeight() * 0.75)});
			falling = false;
		}
	}
	if (stunned) {
		if (SDL_GetTicks() - stunTimer > timeStunned * 1000) {
			normalAttackTimer = specialAttackTimer = SDL_GetTicks();
			ent_->getComponent<Health>()->setInmune(true);
			stunned = false;
		}
		else return;
	}

	p = ent_->getComponent<PhysicsComponent>();

	//Comportamiento
	Transform* pTr = player->getComponent<Transform>();
	Vector2D pPos = pTr->getPosition();
	if (pPos.getY() < tr_->getPosition().getY() ) //Si el jugador no está a su alcance
	{
		if (!outRage) {
			outRage = true; waitTimer = SDL_GetTicks();
		}
		else {
			Vector2D dirMov = { (Vector2D{(float)startX, tr_->getPosition().getY()}) - (tr_->getPosition() + Vector2D{tr_->getWidth() / 2,0}) };
			if (SDL_GetTicks() - waitTimer < maxWait || (dirMov.magnitude() <= 30)) {
				p->setVelocity(Vector2D{ 0, 0 });
				if ((SDL_GetTicks() - specialAttackTimer >= timeSpecialAttack) && (player->getComponent<PhysicsComponent>()->isGrounded() && !player->getComponent<PhysicsComponent>()->isClimbing())) {
					spawnPillars();
				}
				if (SDL_GetTicks() - normalAttackTimer >= timeNormalAttack) shootAtPlayer();
			}
			else {
				p->setVelocity(dirMov.normalize());
				if (fAnim_->getState() != ATTACK_FIREBOSS)
					tr_->setPosition(tr_->getPosition() + Vector2D{ p->getVelocity().getX(),0 });
			}
		}
		
	}
	else{
		if (outRage) outRage = false;
		Vector2D dirMov = { (pPos + Vector2D{pTr->getWidth() / 2,0}) - (tr_->getPosition() + Vector2D{tr_->getWidth() / 2,0}) };
		if (dirMov.magnitude() <= 200) {
			if (SDL_GetTicks() - normalAttackTimer >= timeNormalAttack) meleePlayer();
			p->setVelocity(Vector2D{ 0, 0 });
		}
		else {
			p->setVelocity(dirMov.normalize());
			if(fAnim_->getState() != ATTACK_FIREBOSS)
			tr_->setPosition(tr_->getPosition() + Vector2D{ p->getVelocity().getX(),0 });
		}
	}
	if (fAnim_->getState() != ATTACK_FIREBOSS) {
		fImg = ent_->getComponent<FramedImage>();
		fImg->flipTexture(false);
		if (abs(p->getVelocity().getX()) > 0) {
			fAnim_->setState(AMBUSH_FIREBOSS);
			if (p->getVelocity().getX() < 0) fImg->flipTexture(true);
		}
		else {
			fAnim_->setState(IDLE_FIREBOSS);
			if(pTr->getPosition().getX() < tr_->getPosition().getX()) fImg->flipTexture(true); 
		}
	}
}
void FireBossComponent::spawnPillars()
{
	Transform* pTr = player->getComponent<Transform>();
	Vector2D pPos = pTr->getPosition();
	constructors::firePillar(mngr_, "firePillar", pPos.getX() - pTr->getWidth() / 2, pPos.getY() + pTr->getHeight() / 2, 1);
	specialAttackTimer = SDL_GetTicks();
}

void FireBossComponent::shootAtPlayer()
{
	if (fAnim_->getState() != DIE_FIREBOSS) fAnim_->setState(ATTACK_FIREBOSS);
	Vector2D position = tr_->getPosition();
	Transform* pTr = player->getComponent<Transform>();
	Vector2D direction = pTr->getPosition() - position;
	direction = direction.normalize() * 2;
	constructors::bullet(mngr_, "spikeBall", position.getX()+tr_->getWidth()/2, position.getY() + tr_->getHeight()/2, 50, direction, ent_, ecs::Fire, 1);
	normalAttackTimer = SDL_GetTicks();
}

void FireBossComponent::meleePlayer()
{
	fAnim_->setState(ATTACK_FIREBOSS);
	Transform* pTr = player->getComponent<Transform>();
	if (SDL_HasIntersection(&pTr->getRect(), &tr_->getRect())) {
		bool d = false;
		if (tr_->getPosition().getX() + tr_->getWidth() / 2 <= pTr->getPosition().getX() + pTr->getWidth() / 2) d = true;
		player->getComponent<Health>()->recieveDamage(ecs::Fire, d);
	}
	normalAttackTimer = SDL_GetTicks();
}


void FireBossComponent::stunBoss()
{
	stunned = true; 
	stunTimer = SDL_GetTicks();
	ent_->getComponent<Health>()->setInmune(false);
}
void FireBossComponent::resetBoss() {
	start = false;
	ent_->getComponent<Health>()->resetHealth();
	startPosition();
}


