#include "Gun.h"
#include"../ecs/Entity.h"
#include "Image.h"
#include "DisableOnExit.h"

void Gun::initComponent() {
	transform = ent_->getComponent<Transform>();
}

void Gun::update(){
	if (!canShot && SDL_GetTicks() - startTime >= 250.0f) { //Si no se puede disparar y ha pasado un tiempo, se habilita otra vez el disparo
		canShot = true;
		startTime = SDL_GetTicks();
	}
}

void Gun::handleInput() {
	if (InputHandler::instance()->isKeyJustDown(SDLK_s) && canShot) { //Si se aprieta al espacio y se puede disparar
			auto b = mngr_->addEntity(ecs::_grp_BULLETS); //Se añade una entidad al grupo de las balas

			Vector2D bPos = transform->getPosition()
				+ Vector2D(transform->getWidth() / 2.0f, transform->getHeight() / 2.0f)
				- Vector2D(0.0f, transform->getHeight() / 2.0f + 5.0f + 12.0f).rotate(transform->getRotation())
				- Vector2D(2.0f, 10.0f);

			Vector2D bVel = Vector2D(0.0f, -1.0f).rotate(transform->getRotation()) * (transform->getVelocity().magnitude() + 5.0f);

			b->addComponent<Transform>(bPos, bVel, 5, 20, transform->getRotation()); 
			b->addComponent<Image>(&sdlutils().images().at("fire"));
			b->addComponent<DisableOnExit>(); //Se le añaden los componentes que tiene una bala
			startTime = SDL_GetTicks();
			sdlutils().soundEffects().at("fire").play(0, 2);
		canShot = false; //Se deshabilita el disparo
	}
}