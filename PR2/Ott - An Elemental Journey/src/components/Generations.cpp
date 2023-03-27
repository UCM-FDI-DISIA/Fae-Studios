#include "Generations.h"
#include "Transform.h"
#include "PhysicsComponent.h"
#include "EnemyMovement.h"
#include "EnemyAttack.h"
#include "SlimeStates.h"
#include "Health.h"
#include "EnemyMeleeAttack.h"
#include "../game/Constructors.h"
#include "../states/GameStateMachine.h"

void Generations::Divide() {
	auto health_ = ent_->getComponent<Health>();
	// me guardo la pos actual del bicho grande para crear a cada bichito en su x+50 y su x-50
	Vector2D pos = { ent_->getComponent<Transform>()->getPosition().getX() - 50, ent_->getComponent<Transform>()->getPosition().getY() };
	// bucle que se hace el numero de veces que bichitos quiero (2)
	for (int i = 0; i < 2; i++) {
		// añado todos los componentes necesarios de un slime
		float scale = 1.0f;
		for (int i = 2; i >= getGeneration() - 1; --i) {
			scale *= 2 / 3.0f;
		}
		auto slime = constructors::eSlime(mngr_, ent_->getComponent<FramedImage>()->getTexture(), (int)pos.getX(), (int)pos.getY(), scale, getGeneration() - 1, health_->getMaxHealth() / 2 - 1, health_->getElement(), ent_->getComponent<PhysicsComponent>()->getLookDirection(), room);
		static_cast<PlayState*>(stateMachine().currentState())->addEnemy(slime, room);
		pos = Vector2D(pos.getX() + 50, pos.getY());
	}
}
