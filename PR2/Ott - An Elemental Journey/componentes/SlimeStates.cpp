#include "SlimeStates.h"
#include "../Src/Entity.h"
#include "../Src/Manager.h"
#include "EnemyMovement.h"


void SlimeStates::initComponent()
{
	player = mngr_->getPlayer();
	attack = ent_->getComponent<EnemyAttack>();
	physics = ent_->getComponent<PhysicsComponent>();
	transform = ent_->getComponent<Transform>();
	actGen = ent_->getComponent<Generations>();
	// inicializo la zona de da�o del slime (supuesta zona en su cabeza en la que el jugador puede hacerle da�o aunque por ahora no afecta en nada)
	damageZone.y = transform->getPos().getY(); damageZone.x = transform->getPos().getX(); damageZone.w = transform->getW(); damageZone.h = transform->getH() / actGen->getGeneration();
}

// cambia de pos la zona de da�o cuando se tumba
void SlimeStates::layDownAdjust()
{
	int aux = damageZone.h;
	damageZone.h = damageZone.w; damageZone.w = aux;
	damageZone.y += transform->getH() - damageZone.h;
	if (physics->getLookDirection()) damageZone.x += transform->getW() - damageZone.w;
}

// cambia de pos la zona de da�o cuando se levanta
void SlimeStates::getUpAdjust()
{
	int aux = damageZone.h;
	damageZone.h = damageZone.w; damageZone.w = aux;
	damageZone.y = transform->getPos().getY(); damageZone.x = transform->getPos().getX();
}

// basicamente comprueba si esta en estado de "tumbarse" o "levantarse" y ajusta el rect�ngulo en el que puede recibir da�o y cambia el booleano para que s�lo se haga una vez
void SlimeStates::update()
{
	cout << attack->getState() << endl;
	if (attack->getState() == attack->preparing) {
		if (ajusta) { layDownAdjust(); ajusta = false; }
	}
	else if (attack->getState() == attack->afterAttack) {
		if (!ajusta) { getUpAdjust(); ajusta = true; }
	}
}
