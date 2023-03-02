#include "SlimeAttack.h"
#include "../Src/Entity.h"
#include "../Src/Manager.h"
#include "Generations.h"
#include "EnemyMovement.h"

void SlimeAttack::layDownAdjust()
{
	int aux = damageZone.h;
	damageZone.h = damageZone.w; damageZone.w = aux;
	damageZone.y += transform->getH() - damageZone.h;
	if (physics->getVelocity().getX() > 0) damageZone.x += transform->getW() - damageZone.w;
}

void SlimeAttack::getUpAdjust()
{
	int aux = damageZone.h;
	damageZone.h = damageZone.w; damageZone.w = aux;
	damageZone.y = transform->getPos().getY(); damageZone.x = transform->getPos().getX();
}

void SlimeAttack::divide()
{
	auto slime = mngr_->addEntity(ecs::_grp_CHARACTERS);
	slime->addComponent<Transform>(transform->getPos(), ent_->getComponent<Generations>()->getGeneration() - 1, ent_->getComponent<Generations>()->getGeneration() - 1);
	slime->addComponent<PhysicsComponent>(); //Calcular offset
	slime->addComponent<Generations>(ent_->getComponent<Generations>()->getGeneration() - 1);
	slime->addComponent<EnemyMovement>(); //Calcular trigger
	slime->addComponent<EnemyAttack>(); //Calcular trigger
	slime->addComponent<SlimeAttack>();
}

void SlimeAttack::initComponent()
{
	attack = ent_->getComponent<EnemyAttack>();
	physics = ent_->getComponent<PhysicsComponent>();
	transform = ent_->getComponent<Transform>();
	health = ent_->getComponent<Health>();

	damageZone.y = transform->getPos().getY(); damageZone.x = transform->getPos().getX(); damageZone.w = transform->getW(); damageZone.h = transform->getH() / 3; //Ajustar tamaño de la zona
}

void SlimeAttack::update()
{
	if (attack->getState() == attack->preparing)
		layDownAdjust();
	else if (attack->getState() == attack->afterAttack)
		getUpAdjust();

	if (health <= 0 && ent_->getComponent<Generations>()->getGeneration() > 1) {
		divide();
		divide();
	}
}
