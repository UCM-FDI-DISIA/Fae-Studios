#include "PlayerInput.h"

PlayerInput::PlayerInput()
{
}

void PlayerInput::initComponent()
{
	physics_ = ent_->getComponent<PhysicsComponent>();
	anim_ = ent_->getComponent<PlayerAnimationComponent>();
}

void PlayerInput::update()
{
	Vector2D& playerV = physics_->getVelocity();
	auto input = InputHandler::instance();
	if (input->keyDownEvent()) {
		if (input->isKeyDown(SDLK_z))
		{
			//Defensa
		}
		if (input->isKeyDown(SDLK_LEFT)) {
			//Moviento Izquierda 
			playerV = Vector2D(-1, playerV.getY());
		}
		else if (input->isKeyDown(SDLK_RIGHT))
		{
			//Movimiento derecha
			playerV = Vector2D(1, playerV.getY());
		}

		if (input->isKeyJustDown(SDLK_SPACE)) {
			//Salto
		}
		if (input->isKeyDown(SDLK_q)) {
			//Recuperar vidas
			
		}
		if (input->isKeyDown(SDLK_e) && anim_->getState() != ATTACK) {
			//Ataque
			anim_->setState(ATTACK);
		}
		if (input->isKeyDown(SDLK_a) && anim_->getState() != VANISH) {
			//Cambio elemento
			ent_->getComponent<Health>()->setElement(1);
			ent_->getComponent<FramedImage>()->elementChanged(1);
			anim_->setState(VANISH);
		}
		if (input->isKeyDown(SDLK_d) && anim_->getState() != VANISH) {
			ent_->getComponent<Health>()->setElement(2);
			ent_->getComponent<FramedImage>()->elementChanged(2);
			anim_->setState(VANISH);
		}
		if (input->isKeyDown(SDLK_w) && anim_->getState() != VANISH) {
			ent_->getComponent<Health>()->setElement(3);
			ent_->getComponent<FramedImage>()->elementChanged(3);
			anim_->setState(VANISH);
		}
		if (input->isKeyDown(SDLK_s) && anim_->getState() != VANISH) {
			ent_->getComponent<Health>()->setElement(0);
			ent_->getComponent<FramedImage>()->elementChanged(0);
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
		if (input->isKeyJustUp(SDLK_LEFT)) {
			playerV = Vector2D(0, playerV.getY());
		}
		if (input->isKeyJustUp(SDLK_RIGHT))
		{
			playerV = Vector2D(0, playerV.getY());
		}
		if (input->isKeyUp(SDLK_RIGHT) || input->isKeyUp(SDLK_LEFT)) {
			//ismoving = false;
			playerV = Vector2D(0, playerV.getY());
		}
		if (input->isKeyJustUp(SDLK_SPACE)) {
			//up = false;
		}
		if (input->isKeyUp(SDLK_q)) {
			//physics_->knockback();
			//cout << "knbck" << endl;
		}
		if (input->isKeyJustUp(SDLK_UP)) {
			//upC = false;
		}
		if (input->isKeyJustUp(SDLK_DOWN)) {
			//down = false;
		}
		if (input->isKeyJustUp(SDLK_z)) {
			//defend = false;
		}
	}
}

PlayerInput::~PlayerInput()
{

}

