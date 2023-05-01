#include "SlimeAttack.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "Generations.h"
#include "EnemyMovement.h"

void SlimeAttack::layDownAdjust()
{
	int aux = damageZone.h;
	damageZone.h = damageZone.w; damageZone.w = aux;
	damageZone.y += transform->getHeight() - damageZone.h;
	if (physics->getVelocity().getX() > 0) damageZone.x += transform->getWidth() - damageZone.w;
}

void SlimeAttack::getUpAdjust()
{
	int aux = damageZone.h;
	damageZone.h = damageZone.w; damageZone.w = aux;
	damageZone.y = transform->getPosition().getY(); damageZone.x = transform->getPosition().getX();
}

void SlimeAttack::divide()
{
	auto slime = mngr_->addEntity(ecs::_grp_CHARACTERS);
	slime->addComponent<Transform>(transform->getPosition(), ent_->getComponent<Generations>()->getGeneration() - 1, ent_->getComponent<Generations>()->getGeneration() - 1);
	slime->addComponent<PhysicsComponent>(); //Calcular offset
	slime->addComponent<Generations>(ent_->getComponent<Generations>()->getGeneration() - 1, ent_->getComponent<Generations>()->getRoom());
	slime->addComponent<EnemyMovement>(0.25 * ent_->getComponent<Generations>()->getGeneration()); //Calcular trigger
	slime->addComponent<EnemyAttack>(1500); //Calcular trigger
	slime->addComponent<SlimeAttack>();
}

void SlimeAttack::initComponent()
{
	attack = ent_->getComponent<EnemyAttack>();
	physics = ent_->getComponent<PhysicsComponent>();
	transform = ent_->getComponent<Transform>();
	health = ent_->getComponent<Health>();

	damageZone.y = transform->getPosition().getY(); damageZone.x = transform->getPosition().getX(); damageZone.w = transform->getWidth(); damageZone.h = transform->getHeight() / 3; //Ajustar tamaño de la zona
}

void SlimeAttack::update()
{
	if (attack->getState() == attack->preparing)
		layDownAdjust();
	else if (attack->getState() == attack->afterAttack)
		getUpAdjust();

	if (health->getHealth() <= 0 && ent_->getComponent<Generations>()->getGeneration() > 1) {
		divide();
		divide();
	}
}
