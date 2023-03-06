#include "FighterCtrl.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"
void FighterCtrl::initComponent() {
	transform = ent_->getComponent<Transform>();
}

void FighterCtrl::handleInput() {
	if (InputHandler::instance()->isKeyDown(SDLK_UP)) {
		transform->setVelocity(transform->getVelocity() + Vector2D(0, -1).rotate(transform->getRotation()) * 0.2f);
		if (transform->getVelocity().magnitude() > MAX_VEL) //Si la velocidad supera una velocidad máxima...
			transform->getVelocity().normalize() * MAX_VEL; //Se iguala su velocidad a esa velocidad máxima
		sdlutils().soundEffects().at("thrust1").play(0, -1);
	}

    if (InputHandler::instance()->isKeyDown(SDLK_LEFT))
		transform->setRotation(-5.0f); //Se le restan 5 grados
	else if (InputHandler::instance()->isKeyDown(SDLK_RIGHT))
		transform->setRotation(5.0f); //Se le suman 5 grados
}