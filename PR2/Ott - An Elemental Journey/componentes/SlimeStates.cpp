#include "SlimeStates.h"
#include "../Src/Entity.h"
#include "../Src/Manager.h"
#include "Generations.h"
#include "EnemyMovement.h"


// playerHealth->recieveDamage(health->getElement());

void SlimeStates::initComponent()
{
	player = mngr_->getPlayer();
	attack = ent_->getComponent<EnemyAttack>();
	physics = ent_->getComponent<PhysicsComponent>();
	transform = ent_->getComponent<Transform>();
	//health = ent_->getComponent<Health>();
	//playerHealth = player->getComponent<Health>();
	damageZone.y = transform->getPos().getY(); damageZone.x = transform->getPos().getX(); damageZone.w = transform->getW(); damageZone.h = transform->getH() / 3; //Ajustar tamaño de la zona
}

void SlimeStates::layDownAdjust()
{
	int aux = damageZone.h;
	damageZone.h = damageZone.w; damageZone.w = aux;
	damageZone.y += transform->getH() - damageZone.h;
	if (physics->getLookDirection()) damageZone.x += transform->getW() - damageZone.w;
}

void SlimeStates::getUpAdjust()
{
	int aux = damageZone.h;
	damageZone.h = damageZone.w; damageZone.w = aux;
	damageZone.y = transform->getPos().getY(); damageZone.x = transform->getPos().getX();
}

// crea dos nuevos slime 
//void SlimeStates::divide()
//{
//	for (int i = 0; i < 2; i++) {
//		auto slime = mngr_->addEntity(ecs::_grp_CHARACTERS);
//		slime->addComponent<Transform>(transform->getPos(), ent_->getComponent<Generations>()->getGeneration() - 1, ent_->getComponent<Generations>()->getGeneration() - 1);
//		slime->addComponent<PhysicsComponent>(); //Calcular offset
//		slime->addComponent<Generations>(ent_->getComponent<Generations>()->getGeneration() - 1);
//		slime->addComponent<EnemyMovement>(); //Calcular trigger
//		slime->addComponent<EnemyAttack>(); //Calcular trigger
//		slime->addComponent<SlimeStates>();
//	}
//}


/*probably aquí habrá que ajustar las animaciones tambien idk*/

// basicamente comprueba si esta en estado de "tumbarse" o "levantarse" y ajusta el rectángulo en el que puede recibir daño y cambia el booleano para que sólo se haga una vez
void SlimeStates::update()
{
	if (attack->getState() == attack->preparing) {
		if (ajusta) { layDownAdjust(); ajusta = false; }
	}
	else if (attack->getState() == attack->afterAttack) {
		if (!ajusta) { getUpAdjust(); ajusta = true; }
	}

	// para cuando reciba daño meto ahi la comprobacion
	/*if (health->getHealth() <= 0 && ent_->getComponent<Generations>()->getGeneration() > 1) {
		divide();
		divide();
	}*/
}
