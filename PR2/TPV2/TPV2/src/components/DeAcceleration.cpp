#include "DeAcceleration.h"
#include "../ecs/Entity.h"

void DeAcceleration::initComponent() {
	transform = ent_->getComponent<Transform>();
}
void DeAcceleration::update() {
	transform->setVelocity(transform->getVelocity() * deAccelerationFactor); //En cada frame se reduce la velocidad multiplic�ndola por un factor

	if (transform->getVelocity().magnitude() < minVel) 
		transform->setVelocity(Vector2D(0, 0)); //Si la velocidad llega a su m�nimo se iguala a 0
}
