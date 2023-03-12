#include "Generations.h"
#include "Transform.h"
#include "PhysicsComponent.h"
#include "EnemyMovement.h"
#include "EnemyAttack.h"
#include "SlimeStates.h"
#include "Health.h"
#include "EnemyMeleeAttack.h"

void Generations::Divide() {
	// me guardo la pos actual del bicho grande para crear a cada bichito en su x+50 y su x-50
	Vector2D pos = { ent_->getComponent<Transform>()->getPosition().getX() - 50, ent_->getComponent<Transform>()->getPosition().getY() };
	// bucle que se hace el numero de veces que bichitos quiero (2)
	for (int i = 0; i < 2; i++) {
		// añado todos los componentes necesarios de un slime
		auto slime = mngr_->addEntity(ecs::_grp_CHARACTERS);
		slime->addComponent<Transform>(pos, ent_->getComponent<Transform>()->getWidth() / 1.5, ent_->getComponent<Transform>()->getHeight() / 1.5);
		slime->addComponent<PhysicsComponent>(); //Calcular offset
		slime->addComponent<FramedImage>(ent_->getComponent<FramedImage>()->getTexture(), 2, 21);
		slime->addComponent<Health>(ent_->getComponent<Health>()->getMaxHealth() / 2 - 1, (ent_->getComponent<Health>()->getElement()));
		auto eAttack_ = slime->addComponent<EnemyAttack>(ent_->getComponent<EnemyAttack>()->getTimeBetweenAttacks()); //Calcular trigger
		slime->addComponent<EnemyMovement>(); //Calcular trigger
		auto eAnim_ = slime->addComponent<EnemyAnimationComponent>(anims::SLIME_ANIM);
		auto attack_ = slime->addComponent<EnemyMeleeAttack>();
		slime->addComponent<Generations>(getGeneration() - 1);

		slime->addComponent<SlimeStates>();
		eAttack_->SetRefs(eAnim_, nullptr, attack_);

		pos = Vector2D(pos.getX() + 50, pos.getY());
	}
}
