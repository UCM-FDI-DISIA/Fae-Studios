#include "Acceleration.h"

void Acceleration:: initComponent(){
	player = mngr_->getPlayer();
	physics = ent_->getComponent<PhysicsComponent>();
	transform = ent_->getComponent<Transform>();
	playerTransform = player->getComponent<Transform>();
}
void Acceleration ::update()
{
	Vector2D distance = playerTransform->getPosition() - transform->getPosition();
	float aux= distance.magnitude();

	physics->setVelocity(physics->getVelocity()*(aux/100));

	std::cout << "Vel DIS: " << distance << std::endl;

	std::cout << "Vel PLAY: " << playerTransform->getPosition() << std::endl;

	std::cout << "Vel POS: " << transform->getPosition() << std::endl;
	std::cout << "Vel AUX: " << aux / 100 << std::endl;
}
