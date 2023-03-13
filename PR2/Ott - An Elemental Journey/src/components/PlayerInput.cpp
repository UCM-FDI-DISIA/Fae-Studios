#include "PlayerInput.h"
#include "../states/PlayState.h"
#include "../states/GameStateMachine.h"

PlayerInput::PlayerInput()
{

}

void PlayerInput::initComponent()
{
	physics_ = ent_->getComponent<PhysicsComponent>();
	anim_ = ent_->getComponent<PlayerAnimationComponent>();
	attack_ = ent_->getComponent<PlayerAttack>();
	image_ = ent_->getComponent<FramedImageOtt>();
	health_ = ent_->getComponent<Health>();
	horizontalSpeed = physics_->getHorizontalSpeed();
}

void PlayerInput::update()
{
	Vector2D& playerV = physics_->getVelocity();
	auto input = InputHandler::instance();
	auto state = anim_->getState();
	if (input->keyDownEvent() && state != DIE) {
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
			ent_->getComponent<AttackCharger>()->addCharge(5);
		}
		if (input->isKeyDown(SDLK_f)) {
			//Recuperar vidas
			static_cast<PlayState*>(GameStateMachine::instance()->getPlayState())->checkInteraction();
		}
		if (input->isKeyDown(SDLK_x)) {
			//Recuperar vidas
			health_->recieveDamage(ecs::Earth);
		}
		if (state != VANISH) {
			if (input->isKeyDown(SDLK_z))
			{
				//Defensa
				image_->shielded(true);
				physics_->slowed();
			}
			if (input->isKeyJustDown(SDLK_e) && anim_->getState() != ATTACK && !attack) {
				//Ataque
				attack = true;
				attackTimer = SDL_GetTicks();
				
			}
			if (input->isKeyDown(SDLK_a)) {
				//Cambio elemento
				anim_->changeElem(ecs::Earth);
				anim_->setState(VANISH);
			}
			if (input->isKeyDown(SDLK_d)) {
				anim_->changeElem(ecs::Water);
				anim_->setState(VANISH);
			}
			if (input->isKeyDown(SDLK_w)) {
				anim_->changeElem(ecs::Fire);
				anim_->setState(VANISH);
			}
			if (input->isKeyDown(SDLK_s)) {
				anim_->changeElem(ecs::Light);
				anim_->setState(VANISH);
			}
		}
		if (input->isKeyDown(SDLK_UP)) {
			//Trepar
		}
		if (input->isKeyDown(SDLK_DOWN)) {
			//Agacharse?
		}
	}
	else if (state == DIE) playerV = Vector2D(0, playerV.getY());
	if (input->keyUpEvent()) {
		if (state != DIE) {
			if (input->isKeyUp(SDLK_LEFT) && input->isKeyUp(SDLK_RIGHT)) {
				playerV = Vector2D(0, playerV.getY());
			}
			else {
				if (input->isKeyJustUp(SDLK_RIGHT)) {
					playerV = playerV - Vector2D(horizontalSpeed, 0);
					if (playerV.getX() < -horizontalSpeed) playerV = Vector2D(-horizontalSpeed, playerV.getY());

				}
				if (input->isKeyJustUp(SDLK_LEFT)) {
					playerV = playerV - Vector2D(-horizontalSpeed, 0);
					if (playerV.getX() > horizontalSpeed) playerV = Vector2D(horizontalSpeed, playerV.getY());
				}
			}
			if (input->isKeyJustUp(SDLK_e) && attack) {
				attack = false;
				AttackCharger* pChargedAttackComp = ent_->getComponent<AttackCharger>();
				bool canChargeAttack = pChargedAttackComp->hasChargedAttack();
				bool isCharged = (canChargeAttack && SDL_GetTicks() - attackTimer >= chargedAttackTime * 1000);
				anim_->setState(ATTACK);
				attack_->startAttack(isCharged);
				if (isCharged) {
					int& numCharges = pChargedAttackComp->getCharge(); numCharges = 0;
				}
			}
		}
		if (input->isKeyJustUp(SDLK_z)) {
			//defend = false;
			image_->shielded(false);
		}
	}

	//Interacción con una enredadera
	auto vineCol = static_cast<PlayState*>(GameStateMachine::instance()->getPlayState())->checkCollisionWithVine();
	int speed = 1;
	if (vineCol.first) {
		std::cout << "tocando enredadera!" << std::endl;
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

PlayerInput::~PlayerInput()
{

}
