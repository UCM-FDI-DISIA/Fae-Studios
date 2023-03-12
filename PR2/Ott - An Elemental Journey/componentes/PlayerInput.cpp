#include "PlayerInput.h"
#include "Health.h"

PlayerInput::PlayerInput()
{
}

void PlayerInput::initComponent()
{
	physics_ = ent_->getComponent<PhysicsComponent>();
	anim_ = ent_->getComponent<PlayerAnimationComponent>();
	attack_ = ent_->getComponent<PlayerAttack>();
	horizontalSpeed = physics_->getHorizontalSpeed();
}

void PlayerInput::update()
{
	if (active) {
		Vector2D& playerV = physics_->getVelocity();
		auto input = InputHandler::instance();
		if (input->keyDownEvent()) {
		
			if (input->isKeyDown(SDLK_LEFT)) {
				//Moviento Izquierda 
				playerV = Vector2D(-horizontalSpeed, playerV.getY());
				physics_->lookDirection(false);
			}
			if (input->isKeyDown(SDLK_RIGHT))
			{
				//Movimiento derecha
				playerV = Vector2D(horizontalSpeed, playerV.getY());
				physics_->lookDirection(true);
			}

			if (input->isKeyDown(SDLK_SPACE)) {
				//Salto
				physics_->jump();
			}
			if (input->isKeyDown(SDLK_q)) {
				//Recuperar vidas
				physics_->knockback();
			}
			if (input->isKeyDown(SDLK_f)) {
				//Recuperar vidas
				mngr_->checkInteraction();
			}
			if (input->isKeyDown(SDLK_x)) {
				//Recuperar vidas
				ent_->getComponent<Health>()->recieveDamage(ecs::Earth);
			}
			if (input->isKeyDown(SDLK_e) && anim_->getState() != ATTACK) {
				//Ataque
				anim_->setState(ATTACK);
				attack_->startAttack();
			}
			if (input->isKeyDown(SDLK_z))
			{
				//Defensa
				ent_->getComponent<FramedImageOtt>()->shielded(true);
				physics_->slowed();
			}
			if (input->isKeyDown(SDLK_a) && anim_->getState() != VANISH) {
				//Cambio elemento
				anim_->changeElem(ecs::Earth);
				anim_->setState(VANISH);
			}
			if (input->isKeyDown(SDLK_d) && anim_->getState() != VANISH) {
				anim_->changeElem(ecs::Water);
				anim_->setState(VANISH);
			}
			if (input->isKeyDown(SDLK_w) && anim_->getState() != VANISH) {
				anim_->changeElem(ecs::Fire);
				anim_->setState(VANISH);
			}
			if (input->isKeyDown(SDLK_s) && anim_->getState() != VANISH) {
				anim_->changeElem(ecs::Light);
				anim_->setState(VANISH);
			}
			if (input->isKeyDown(SDLK_UP)) {
				//Trepar
			}
			if (input->isKeyDown(SDLK_DOWN)) {
				//Agacharse?
			}
		}
		if (input->keyUpEvent()) {
			if (input->isKeyUp(SDLK_LEFT) && input->isKeyUp(SDLK_RIGHT)) {
				playerV = Vector2D(0, playerV.getY());
			}
			else {
				if (input->isKeyJustUp(SDLK_RIGHT)) {
					playerV = playerV - Vector2D(horizontalSpeed,0);
					if (playerV.getX() < -horizontalSpeed) playerV = Vector2D(-horizontalSpeed, playerV.getY());
				
				}
				if (input->isKeyJustUp(SDLK_LEFT)) {
					playerV = playerV - Vector2D(-horizontalSpeed, 0);
					if (playerV.getX() > horizontalSpeed) playerV = Vector2D(horizontalSpeed, playerV.getY());
				}
			}
			if (input->isKeyJustUp(SDLK_z)) {
				//defend = false;
				ent_->getComponent<FramedImageOtt>()->shielded(false);
			}

		}

		//Interacción con una enredadera
		auto vineCol = mngr_->checkCollisionWithVine();
		int speed = 1;
		if (vineCol.first) {
			if (input->isKeyDown(SDLK_UP) && vineCol.second) {
				physics_->setClimbing(true, -speed);
			}
			else if (input->isKeyDown(SDLK_DOWN)) {
				physics_->setClimbing(true, speed);
			}
			else physics_->setClimbing(true, 0);
		}
		else physics_->setClimbing(false, 0);
	}
	else {
		Vector2D& playerV = physics_->getVelocity();
		playerV = Vector2D(0, 0);
	}
}

PlayerInput::~PlayerInput()
{

}

