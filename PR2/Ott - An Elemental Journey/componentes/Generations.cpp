#include "Generations.h"
#include "Transform.h"
#include "PhysicsComponent.h"
#include "EnemyMovement.h"
#include "EnemyAttack.h"
#include "SlimeStates.h"
#include "Health.h"

void Generations::Divide() {
	// me guardo la pos actual del bicho grande para crear a cada bichito en su x+50 y su x-50
	Vector2D pos = { ent_->getComponent<Transform>()->getPos().getX() - 50, ent_->getComponent<Transform>()->getPos().getY() };
	// bucle que se hace el numero de veces que bichitos quiero (2)
	for (int i = 0; i < 2; i++) {
		// añado todos los componentes necesarios de un slime
		auto slime = mngr_->addEntity(ecs::_grp_CHARACTERS);
		slime->addComponent<Transform>(pos, ent_->getComponent<Transform>()->getW()/1.5, ent_->getComponent<Transform>()->getH()/1.5);
		slime->addComponent<FramedImageEnemy>(ent_->getComponent<FramedImageEnemy>()->getTexture());
		slime->addComponent<Health>(ent_->getComponent<Health>()->getMaxHealth() - 1, (ent_->getComponent<Health>()->getElement()));
		slime->addComponent<PhysicsComponent>(); //Calcular offset
		slime->addComponent<Generations>(getGeneration() - 1);
		slime->addComponent<EnemyMovement>(); //Calcular trigger
		slime->addComponent<EnemyAttack>(ent_->getComponent<EnemyAttack>()->getPhase1Time(), ent_->getComponent<EnemyAttack>()->getPhase2Time(),
			ent_->getComponent<EnemyAttack>()->getPhase3Time(), ent_->getComponent<EnemyAttack>()->getPhase4Time()); //Calcular trigger
		slime->addComponent<SlimeStates>();
		slime->addComponent<EnemyAnimationComponent>(anims::RANGE_ANIM);
		pos = pos + 50;
	}
}