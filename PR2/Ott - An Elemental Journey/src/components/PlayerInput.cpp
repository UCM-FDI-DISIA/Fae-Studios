#include "PlayerInput.h"
#include "FramedImage.h"
#include "Health.h"

void PlayerInput::initComponent()
{
	physics_ = ent_->getComponent<PhysicsComponent>();
	anim_ = ent_->getComponent<PlayerAnimationComponent>();
	horizontalSpeed = physics_->getHorizontalSpeed();
}

void PlayerInput::update()
{
	Vector2D& playerV = physics_->getVelocity();
	auto input = InputHandler::instance();
	if (input->keyDownEvent()) {
		
		if (input->isKeyDown(SDLK_LEFT)) {
			//Moviento Izquierda 
			playerV = Vector2D(-horizontalSpeed, playerV.getY());
			physics_->lookDirection(false);
			//cout << "IZQ" << endl;
		}
		if (input->isKeyDown(SDLK_RIGHT))
		{
			//Movimiento derecha
			//cout << "DER" << endl;
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
		if (input->isKeyDown(SDLK_e) && anim_->getState() != ATTACK) {
			//Ataque
			anim_->setState(ATTACK);
		}
		if (input->isKeyDown(SDLK_z))
		{
			//Defensa
			//cout << "Defensa" << endl;
			ent_->getComponent<FramedImageOtt>()->shielded(true);
			physics_->slowed();
		}
		if (input->isKeyDown(SDLK_a) && anim_->getState() != VANISH) {
			//Cambio elemento
			ent_->getComponent<Health>()->setElement(1);
			ent_->getComponent<FramedImageOtt>()->elementChanged(1);
			anim_->setState(VANISH);
		}
		if (input->isKeyDown(SDLK_d) && anim_->getState() != VANISH) {
			ent_->getComponent<Health>()->setElement(2);
			ent_->getComponent<FramedImageOtt>()->elementChanged(2);
			anim_->setState(VANISH);
		}
		if (input->isKeyDown(SDLK_w) && anim_->getState() != VANISH) {
			ent_->getComponent<Health>()->setElement(3);
			ent_->getComponent<FramedImageOtt>()->elementChanged(3);
			anim_->setState(VANISH);
		}
		if (input->isKeyDown(SDLK_s) && anim_->getState() != VANISH) {
			ent_->getComponent<Health>()->setElement(0);
			ent_->getComponent<FramedImageOtt>()->elementChanged(0);
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
			//cout << "parar" << endl;
			playerV = Vector2D(0, playerV.getY());
		}
		else {
			if (input->isKeyJustUp(SDLK_RIGHT)) {
				//cout << "parar de ir a la derecha" << endl;
				playerV = playerV - Vector2D(horizontalSpeed,0);
				if (playerV.getX() < -horizontalSpeed) playerV = Vector2D(-horizontalSpeed, playerV.getY());
				
			}
			if (input->isKeyJustUp(SDLK_LEFT)) {
				//cout << "parar de ir a la izquieda" << endl;
				playerV = playerV - Vector2D(-horizontalSpeed, 0);
				if (playerV.getX() > horizontalSpeed) playerV = Vector2D(horizontalSpeed, playerV.getY());
			}
		}

		if (input->isKeyJustUp(SDLK_UP)) {
			//upC = false;
		}
		if (input->isKeyJustUp(SDLK_DOWN)) {
			//down = false;
		}
		if (input->isKeyJustUp(SDLK_z)) {
			//defend = false;
			ent_->getComponent<FramedImageOtt>()->shielded(false);
		}
	}
}

