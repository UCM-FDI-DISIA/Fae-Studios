#include "Acceleration.h"
#include "../sdlutils/InputHandler.h"

void Acceleration:: initComponent(){
	player = mngr_->getPlayer();
	physics = ent_->getComponent<PhysicsComponent>();
	transform = ent_->getComponent<Transform>();
	playerTransform = player->getComponent<Transform>();
}
void Acceleration::update()
{
	if (!start)
	{
		if (transform->getPosition().getY() - playerTransform->getPosition().getY() <= -10) {
			start = true;
			physics->setVelocity({ 1, 0 });
			speed = { 1,0 };
		}
	}
	else {
		Vector2D distance = Vector2D(((playerTransform->getPosition().getX() + playerTransform->getWidth() / 2) -
			(transform->getPosition().getX() + transform->getWidth() / 2)),
			((playerTransform->getPosition().getY() + playerTransform->getHeight() / 2) -
				(transform->getPosition().getY() + transform->getHeight() / 2)));


		float aux = distance.magnitude();
		auto input = InputHandler::instance();

		if (!waiting) {
			Vector2D vecAux;
			//derecha
			if (physics->getVelocity().getX() > 0.0f )vecAux = { aux / 750,0 };
			//izquierda
			else if (physics->getVelocity().getX() < 0.0f )vecAux = { -aux / 750,0 };
			//arriba
			else if (physics->getVelocity().getY() < 0.0f )vecAux = { 0,-aux / 750 };
			//abajo
			else if (physics->getVelocity().getY() > 0.0f) vecAux = { 0,aux / 750 };
			physics->setVelocity(vecAux);
		}
		else {

			physics->setVelocity({ 0,0 });
		}

		if (InputHandler::instance()->isKeyJustDown(SDLK_k))
		{
			waiting = false;
			physics->setVelocity(speed);
		}
	}
}
